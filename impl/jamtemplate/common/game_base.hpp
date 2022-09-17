#ifndef JAMTEMPLATE_GAMEBASE_HPP
#define JAMTEMPLATE_GAMEBASE_HPP

#include <game_interface.hpp>
#include <game_object.hpp>
#include <chrono>
#include <memory>

namespace jt {
class GameBase : public GameInterface,
                 public GameObject,
                 public std::enable_shared_from_this<GameBase> {
public:
    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    GameBase(jt::GfxInterface& gfx, jt::InputManagerInterface& input, jt::AudioInterface& audio,
        jt::StateManagerInterface& stateManager, jt::LoggerInterface& logger,
        jt::ActionCommandManagerInterface& actionCommandManager, jt::CacheInterface& cache);

    void runOneFrame();

    GfxInterface& gfx() const override;

    InputGetInterface& input() override;

    AudioInterface& audio() override;

    StateManagerInterface& stateManager() override;

    LoggerInterface& logger() override;

    ActionCommandManagerInterface& actionCommandManager() override;

    CacheInterface& cache() override;

    /// Start game
    /// \param gameloop_function
    virtual void startGame(GameLoopFunctionPtr gameloop_function) = 0;

    void reset() override;

protected:
    std::weak_ptr<GameInterface> getPtr() override;

    // overwritten functions from GameObject
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    GfxInterface& m_gfx;

    InputManagerInterface& m_inputManager;

    AudioInterface& m_audio;

    StateManagerInterface& m_stateManager;

    LoggerInterface& m_logger;

    ActionCommandManagerInterface& m_actionCommandManager;

    CacheInterface& m_cache;

    std::chrono::steady_clock::time_point m_timeLast {};

    float m_lag { 0.0f };
    float m_timePerUpdate { 0.005f };
    int m_maxNumberOfUpdateIterations { 100 };
};

} // namespace jt

#endif
