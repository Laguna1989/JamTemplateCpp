﻿#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "Rect.hpp"
#include "Rendertarget.hpp"
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <memory>
#include <string>

namespace jt {

class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(unsigned int w, unsigned int h, float zoom, std::string const& title);

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    void runGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    virtual float getZoom() const override;

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<SDL_Window> m_window;
    float m_zoom;

    jt::Recti m_srcRect;
    jt::Recti m_destRect;
    jt::Vector2 m_fullsize;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;
    void resetShake() override;

    std::shared_ptr<Mix_Music> m_music;
    void PlayMusic(std::string const& fileName) override;
    void StopMusic() override;
    void SetMusicVolume(float v) override;
};

} // namespace jt
#endif
