#include "game.hpp"
#include "drawable_impl.hpp"
#include "game_state.hpp"
#include "input/input_manager.hpp"
#include "random/random.hpp"
#include "rect.hpp"
#include "texture_manager_impl.hpp"
#include "vector.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#ifdef ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer,
    std::shared_ptr<CamInterface> camera, std::shared_ptr<StateManagerInterface> stateManager)
    : GameBase { window, input, musicPlayer, camera, stateManager }
{
    auto const width = getRenderWindow()->getSize().x();
    auto const height = getRenderWindow()->getSize().y();

    auto const scaledWidth = static_cast<int>(width / getCamera()->getZoom());
    auto const scaledHeight = static_cast<int>(height / getCamera()->getZoom());
    m_srcRect = jt::Recti { 0, 0, scaledWidth, scaledHeight };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };

    m_renderTarget = getRenderWindow()->createRenderTarget();
    TTF_Init();
    m_textureManager = std::make_shared<jt::TextureManagerImpl>(m_renderTarget);

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

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    setupRenderTarget();
#ifdef ENABLE_WEB
    emscripten_set_main_loop(gameloop_function, 0, 1);
#else
    while (getRenderWindow()->isOpen()) {
        getRenderWindow()->checkForClose();
        gameloop_function();
    }
#endif
}
void Game::doUpdate(float const elapsed)
{
    m_stateManager->getCurrentState()->update(elapsed);
    getCamera()->update(elapsed);

    jt::Vector2 const mpf = getRenderWindow()->getMousePosition() / getCamera()->getZoom();

    input()->update(MousePosition { mpf.x() + getCamera()->getCamOffset().x(),
                        mpf.y() + getCamera()->getCamOffset().y(), mpf.x(), mpf.y() },
        elapsed);

    DrawableImpl::setCamOffset(-1.0f * getCamera()->getCamOffset());
};

void Game::doDraw() const
{

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    // for reasons this can not be a member.
    auto* const t = SDL_CreateTexture(getRenderTarget().get(), SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, static_cast<int>(m_srcRect.width()),
        static_cast<int>(m_srcRect.height()));

    // render to the small texture first
    SDL_SetRenderTarget(getRenderTarget().get(), t);
    SDL_RenderClear(getRenderTarget().get());
    m_stateManager->getCurrentState()->draw();

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
    m_renderWindow->display();
    SDL_RenderPresent(getRenderTarget().get());

    SDL_DestroyTexture(t);
};

} // namespace jt
