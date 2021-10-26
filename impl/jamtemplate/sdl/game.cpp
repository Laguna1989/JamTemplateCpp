#include "game.hpp"
#include "drawable_impl.hpp"
#include "game_state.hpp"
#include "input_manager.hpp"
#include "random.hpp"
#include "rect.hpp"
#include "texture_manager.hpp"
#include "vector.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef ENABLE_WEB
#include <emscripten.h>
#endif

#include <iostream>

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer,
    std::shared_ptr<CamInterface> camera)
    : GameBase { camera }
    , m_input { input }
    , m_musicPlayer { musicPlayer }
{
    m_camera->setZoom(zoom);
    auto const width = window->getSize().x();
    auto const height = window->getSize().y();

    auto const scaledWidth = static_cast<int>(width / zoom);
    auto const scaledHeight = static_cast<int>(height / zoom);
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };

    m_window = window;

    m_renderTarget = m_window->createRenderTarget();
    TTF_Init();
    TextureManager::setRenderer(m_renderTarget);

    // important fix for SDL_Mixer: OpenAudio has to be called before Mix_Init,
    // otherwise ogg is not supported.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        std::cout << "cannot OpenAudio: " << Mix_GetError() << std::endl;
    }
    if (Mix_Init(MIX_INIT_OGG) != 0) {
        std::cout << "cannot Mix_Init: " << Mix_GetError() << std::endl;
    }
}

void Game::setupRenderTarget() { }

void Game::startGame(std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
{
    switchState(InitialState);
#ifdef ENABLE_WEB
    emscripten_set_main_loop(gameloop_function, 0, 1);
#else
    while (m_window->isOpen()) {
        m_window->checkForClose();
        gameloop_function();
    }
#endif
}

void Game::setRenderTarget(std::shared_ptr<jt::renderTarget> rt)
{
    if (rt == nullptr) {
        throw std::invalid_argument { "cannot set nullptr rendertarget" };
    }
    m_renderTarget = rt;
}

std::shared_ptr<jt::renderTarget> Game::getRenderTarget() const { return m_renderTarget; }

void Game::doUpdate(float const elapsed)
{
    jt::Vector2 const mpf = m_window->getMousePosition() / getCamera()->getZoom();

    if (input()) {
        input()->update(MousePosition { mpf.x() + getCamera()->getCamOffset().x(),
            mpf.y() + getCamera()->getCamOffset().y(), mpf.x(), mpf.y() });
    }
    m_state->update(elapsed);

    DrawableImpl::setCamOffset(-1.0f * getCamera()->getCamOffset());
};

void Game::doDraw() const
{
    // for reasons this can not be a member.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    auto* const t = SDL_CreateTexture(getRenderTarget().get(), SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, static_cast<int>(m_srcRect.width()),
        static_cast<int>(m_srcRect.height()));

    // render to the small texture first
    SDL_SetRenderTarget(getRenderTarget().get(), t);
    SDL_RenderClear(getRenderTarget().get());
    m_state->draw();

    // Detach the texture
    SDL_SetRenderTarget(getRenderTarget().get(), nullptr);

    // Now render the texture target to our screen
    SDL_RenderClear(getRenderTarget().get());
    SDL_Rect sourceRect { m_srcRect.left(), m_srcRect.top(), m_srcRect.width(),
        m_srcRect.height() };
    SDL_Rect destRect { static_cast<int>(getCamera()->getShakeOffset().x()),
        static_cast<int>(getCamera()->getShakeOffset().y()), m_destRect.width(),
        m_destRect.height() };
    SDL_RenderCopyEx(getRenderTarget().get(), t, &sourceRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
    SDL_RenderPresent(getRenderTarget().get());

    SDL_DestroyTexture(t);
};

std::shared_ptr<MusicPlayerInterface> Game::getMusicPlayer() { return m_musicPlayer; }

std::shared_ptr<InputManagerInterface> Game::input() { return m_input; }

std::shared_ptr<jt::RenderWindowInterface> Game::getRenderWindow() const { return m_window; }

} // namespace jt
