#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "SmartDrawable.hpp"
#include "TextureManager.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten.h>
#include <iostream>

namespace jt {

Game::Game(unsigned int width, unsigned int height, float zoom, std::string const& title)
{
    m_zoom = zoom;
    m_fullsize = jt::vector2 { static_cast<float>(width), static_cast<float>(height) };

    unsigned int scaledWidth = static_cast<unsigned int>(width / zoom);
    unsigned int scaledHeight = static_cast<unsigned int>(height / zoom);
    m_srcRect = jt::recti(0, 0, scaledWidth, scaledHeight);

    m_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, width, height, 0),
        [](SDL_Window* w) { SDL_DestroyWindow(w); });
    if (!m_window) {
        throw std::logic_error { "Failed to create window." };
    }

    m_renderTarget
        = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(m_window.get(), -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
            [](SDL_Renderer* r) { SDL_DestroyRenderer(r); });
    if (!m_renderTarget) {
        throw std::logic_error { "failed to create renderer." };
    }
    SDL_SetRenderDrawBlendMode(m_renderTarget.get(), SDL_BLENDMODE_BLEND);
    TTF_Init();
    TextureManager::setRenderer(m_renderTarget);
}

void Game::runGame(std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
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

float Game::getZoom() const { return m_zoom; }

void Game::doUpdate(float const elapsed)
{
    jt::InputManager::update(0.0f, 0.0f, 0.0f, 0.0f, elapsed);
    m_state->update(elapsed);
    // TODO
    // jt::vector2 mpf = getRenderWindow()->mapPixelToCoords(
    //     sf::Mouse::getPosition(*getRenderWindow()), *getView());
    // jt::vector2 mpfs
    //     = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow())) /
    //     m_zoom;

    // int const camOffsetix { static_cast<int>(m_CamOffset.x() + getView()->getSize().x / 2) };
    // int const camOffsetiy { static_cast<int>(m_CamOffset.y() + getView()->getSize().y / 2) };

    // getView()->setCenter(
    //     jt::vector2 { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) });
    // SmartDrawable::setCamOffset(getView()->getCenter() - getView()->getSize() * 0.5f);
};

void Game::doDraw() const
{
    // for reasons this can not be a member.
    auto t = SDL_CreateTexture(getRenderTarget().get(), SDL_PIXELFORMAT_RGBA8888,
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
    SDL_Rect rect { m_srcRect.left(), m_srcRect.top(), m_srcRect.width(), m_srcRect.height() };
    SDL_RenderCopyEx(getRenderTarget().get(), t, &rect, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(getRenderTarget().get());

    SDL_DestroyTexture(t);
};

void Game::updateShake(float elapsed)
{
    if (m_shakeOffset.x() != 0 || m_shakeOffset.y() != 0) {
        // TODO
        // getView()->move(-m_shakeOffset.x(), -m_shakeOffset.y());
    }

    if (m_shakeTimer > 0) {

        m_shakeTimer -= elapsed;
        m_shakeInterval -= elapsed;
        if (m_shakeInterval < 0) {
            m_shakeInterval = m_shakeIntervalMax;
            m_shakeOffset.x() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
            m_shakeOffset.y() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
        }
    } else {
        m_shakeOffset.x() = m_shakeOffset.y() = 0;
    }
    // TODO
    // auto v = getView();
    // v->move(m_shakeOffset.x(), m_shakeOffset.y());
    // setView(v);
}

void Game::resetShake()
{
    if (m_shakeOffset.x() != 0 || m_shakeOffset.y() != 0) {
        // TODO
        // getView()->move(-m_shakeOffset.x(), -m_shakeOffset.y());
    }
    m_shakeOffset.x() = m_shakeOffset.y() = 0;
    m_shakeTimer = -1;
    m_shakeStrength = 0;
}

} // namespace jt
