#include "game_base.hpp"
#include "performance_measurement.hpp"
#include <build_info.hpp>
#include <tracy/Tracy.hpp>

#include <string>

jt::GameBase::GameBase(jt::GfxInterface& gfx, jt::InputManagerInterface& input,
    jt::AudioInterface& audio, jt::StateManagerInterface& stateManager, jt::LoggerInterface& logger,
    jt::ActionCommandManagerInterface& actionCommandManager, jt::CacheInterface& cache)
    : m_gfx { gfx }
    , m_inputManager { input }
    , m_audio { audio }
    , m_stateManager { stateManager }
    , m_logger { logger }
    , m_actionCommandManager { actionCommandManager }
    , m_cache { cache }
{
    m_logger.info("git commit hash: " + jt::BuildInfo::gitCommitHash(), { "jt", "build info" });
    m_logger.info("build date: " + jt::BuildInfo::timestamp(), { "jt", "build info" });
}

void jt::GameBase::runOneFrame()
{
    ZoneScopedN("jt::GameBase::runOneFrame");
    m_logger.verbose("runOneFrame", { "jt" });
    m_actionCommandManager.update();

    auto const now = std::chrono::steady_clock::now();
    float const elapsedSeconds
        = std::chrono::duration_cast<std::chrono::microseconds>(now - m_timeLast).count() / 1000.0f
        / 1000.0f;
    m_timeLast = now;

    if (m_age != 0) {
        m_lag += elapsedSeconds;
        gfx().window().checkForClose();
        gfx().window().updateGui(elapsedSeconds);

        int numberOfUpdateOperations = 0;

        // update has to be called at least once per frame
        do {
            update(m_timePerUpdate);
            m_lag -= m_timePerUpdate;

            numberOfUpdateOperations++;
            if (numberOfUpdateOperations >= m_maxNumberOfUpdateIterations) {
                m_logger.warning("number of update operations exceeds maximum of "
                        + std::to_string(m_maxNumberOfUpdateIterations),
                    { "jt", "gameloop" });
                m_lag = 0.0f;
                break;
            }
        } while (m_lag >= m_timePerUpdate);
        draw();
    }

    m_age += elapsedSeconds;
    FrameMark;
}

std::weak_ptr<jt::GameInterface> jt::GameBase::getPtr() { return shared_from_this(); }

void jt::GameBase::reset()
{
    m_logger.info("Game reset", { "jt", "game" });
    gfx().reset();
    m_inputManager.reset();
}

jt::GfxInterface& jt::GameBase::gfx() const { return m_gfx; }

jt::InputGetInterface& jt::GameBase::input() { return m_inputManager; }

jt::AudioInterface& jt::GameBase::audio() { return m_audio; }

jt::StateManagerInterface& jt::GameBase::stateManager() { return m_stateManager; }

jt::LoggerInterface& jt::GameBase::logger() { return m_logger; }

jt::ActionCommandManagerInterface& jt::GameBase::actionCommandManager()
{
    return m_actionCommandManager;
}

jt::CacheInterface& jt::GameBase::cache() { return m_cache; }

std::string getTimeString()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

void jt::GameBase::doUpdate(float const elapsed)
{
    ZoneScopedN("jt::GameBase::doUpdate");
    m_logger.verbose("update game", { "jt" });
    m_stateManager.update(getPtr(), elapsed);
    TracyPlot("GameObjects Alive", static_cast<std::int64_t>(getNumberOfAliveGameObjects()));
    TracyPlot("GameObjects Created", static_cast<std::int64_t>(getNumberOfCreatedGameObjects()));
    m_audio.update(elapsed);
    gfx().update(elapsed);

    jt::Vector2f const mousePosition = gfx().window().getMousePosition() / gfx().camera().getZoom();

    m_inputManager.update(gfx().window().shouldProcessKeyboard(),
        gfx().window().shouldProcessMouse(),
        MousePosition { mousePosition.x + gfx().camera().getCamOffset().x,
            mousePosition.y + gfx().camera().getCamOffset().y, mousePosition.x, mousePosition.y },
        elapsed);
}

void jt::GameBase::doDraw() const
{
    ZoneScopedN("jt::GameBase::doDraw");
    m_logger.verbose("draw game", { "jt" });
    gfx().window().startRenderGui();
    gfx().clear();
    m_stateManager.draw(gfx().target());
    gfx().display();
}
