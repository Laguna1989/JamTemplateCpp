#include "Game.hpp"
#include "DrawableImpl.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "Rect.hpp"
#include "TextureManager.hpp"
#include "Vector.hpp"
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL_ttf.h>
#include <emscripten.h>
#include <iostream>

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
    std::shared_ptr<MusicPlayerInterface> musicPlayer)
    : m_musicPlayer { musicPlayer }
{
    m_camera->setZoom(zoom);
    auto const width = window->getSize().x();
    auto const height = window->getSize().y();

    unsigned int scaledWidth = static_cast<unsigned int>(width / zoom);
    unsigned int scaledHeight = static_cast<unsigned int>(height / zoom);
    m_srcRect = jt::Recti { 0, 0, static_cast<int>(scaledWidth), static_cast<int>(scaledHeight) };
    m_destRect = jt::Recti { 0, 0, static_cast<int>(width), static_cast<int>(height) };

    m_window = window;

    m_renderTarget = m_window->createRenderTarget();
    TTF_Init();
    TextureManager::setRenderer(m_renderTarget);

    // important fix for SDL_Mixer: OpenAudio has to be called before Mix_Init,
    // otherwise ogg is not supported.
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Init(MIX_INIT_OGG);
}

void Game::setupRenderTarget() { }

void Game::startGame(std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
{
    switchState(InitialState);
    emscripten_set_main_loop(gameloop_function, 0, 1);
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
    auto const mousePosition = m_window->getMousePosition();
    float const x = mousePosition.x() / getCamera()->getZoom();
    float const y = mousePosition.y() / getCamera()->getZoom();
    jt::InputManager::update(
        y + getCamera()->getCamOffset().x(), +getCamera()->getCamOffset().y(), x, y, elapsed);
    m_state->update(elapsed);

    DrawableImpl::setCamOffset(-1.0f * getCamera()->getCamOffset());
};

void Game::doDraw() const
{
    // for reasons this can not be a member.
    auto const t = SDL_CreateTexture(getRenderTarget().get(), SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET, static_cast<int>(m_srcRect.width()),
        static_cast<int>(m_srcRect.height()));

    // render to the small texture first
    SDL_SetRenderTarget(getRenderTarget().get(), t);
    SDL_RenderClear(getRenderTarget().get());
    m_state->draw();

    // Detach the texture
    SDL_SetRenderTarget(getRenderTarget().get(), NULL);

    // Now render the texture target to our screen
    SDL_RenderClear(getRenderTarget().get());
    SDL_Rect sourceRect { m_srcRect.left(), m_srcRect.top(), m_srcRect.width(),
        m_srcRect.height() };
    SDL_Rect destRect { static_cast<int>(getCamera()->getShakeOffset().x()),
        static_cast<int>(getCamera()->getShakeOffset().y()), m_destRect.width(),
        m_destRect.height() };
    SDL_RenderCopyEx(getRenderTarget().get(), t, &sourceRect, &destRect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(getRenderTarget().get());

    SDL_DestroyTexture(t);
};

void Game::updateShake(float elapsed) { getCamera()->update(elapsed); }

std::shared_ptr<MusicPlayerInterface> Game::getMusicPlayer() { return m_musicPlayer; }

} // namespace jt
