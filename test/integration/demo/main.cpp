#include <action_commands/action_command_manager.hpp>
#include <action_commands/basic_action_commands.hpp>
#include <audio/audio/audio_impl.hpp>
#include <audio/audio/audio_null.hpp>
#include <cache/cache_impl.hpp>
#include <camera.hpp>
#include <game.hpp>
#include <gfx_impl.hpp>
#include <graphics/logging_render_window.hpp>
#include <graphics/render_window.hpp>
#include <input/gamepad/gamepad_input.hpp>
#include <input/input_manager.hpp>
#include <input/keyboard/keyboard_input.hpp>
#include <input/keyboard/keyboard_input_selected_keys.hpp>
#include <input/mouse/mouse_input.hpp>
#include <log/default_logging.hpp>
#include <log/log_history.hpp>
#include <log/logger.hpp>
#include <logging_camera.hpp>
#include <random/random.hpp>
#include <state_manager/logging_state_manager.hpp>
#include <state_manager/state_manager.hpp>
#include <state_select.hpp>
#include <memory>

std::shared_ptr<jt::GameBase> game;

void gameloop()
{
    if (game) {
        game->runOneFrame();
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    jt::Random::useTimeAsRandomSeed();

    auto logHistory = std::make_shared<jt::LogHistory>();
    jt::CacheImpl cache { nullptr, logHistory };

    jt::Logger logger {};
    jt::createDefaultLogTargets(logger);
    logger.addLogTarget(logHistory);

    auto const mouse = std::make_shared<jt::MouseInput>();
    //    auto const keyboard = std::make_shared<jt::KeyboardInput>();
    auto const keyboard = std::make_shared<jt::KeyboardInputSelectedKeys>();

    keyboard->listenForKey(jt::KeyCode::W);
    keyboard->listenForKey(jt::KeyCode::A);
    keyboard->listenForKey(jt::KeyCode::S);
    keyboard->listenForKey(jt::KeyCode::D);

    keyboard->listenForKey(jt::KeyCode::Left);
    keyboard->listenForKey(jt::KeyCode::Right);
    keyboard->listenForKey(jt::KeyCode::Up);
    keyboard->listenForKey(jt::KeyCode::Down);

    keyboard->listenForKey(jt::KeyCode::C);
    keyboard->listenForKey(jt::KeyCode::V);
    keyboard->listenForKey(jt::KeyCode::I);

    keyboard->listenForKey(jt::KeyCode::Num0);
    keyboard->listenForKey(jt::KeyCode::Num1);
    keyboard->listenForKey(jt::KeyCode::Num2);
    keyboard->listenForKey(jt::KeyCode::Num3);
    keyboard->listenForKey(jt::KeyCode::Num4);
    keyboard->listenForKey(jt::KeyCode::Num5);
    keyboard->listenForKey(jt::KeyCode::Num6);
    keyboard->listenForKey(jt::KeyCode::Num7);
    keyboard->listenForKey(jt::KeyCode::Num8);
    keyboard->listenForKey(jt::KeyCode::Num9);

    keyboard->listenForKey(jt::KeyCode::F10);
    keyboard->listenForKey(jt::KeyCode::F1);

    keyboard->listenForKey(jt::KeyCode::Home);
    keyboard->listenForKey(jt::KeyCode::End);

    keyboard->listenForKey(jt::KeyCode::Escape);
    keyboard->listenForKey(jt::KeyCode::Space);

    auto const gamepad0 = std::make_shared<jt::GamepadInput>(0);
    auto const gamepad1 = std::make_shared<jt::GamepadInput>(1);
    jt::InputManager input { mouse, keyboard, { gamepad0, gamepad1 } };

    jt::RenderWindow window { 800, 600, "jt_demos" };
    jt::LoggingRenderWindow loggingRenderWindow { window, logger };
    jt::Camera camera { 2.0f };

    jt::LoggingCamera loggingCamera { camera, logger };
    jt::GfxImpl gfx { loggingRenderWindow, loggingCamera };

    jt::AudioImpl audio {};
    //    jt::null_objects::AudioNull audio {};

    jt::StateManager stateManager { std::make_shared<StateSelect>() };
    jt::LoggingStateManager loggingStateManager { stateManager, logger };

    jt::ActionCommandManager actionCommandManager { logger };

    game = std::make_shared<jt::Game>(
        gfx, input, audio, loggingStateManager, logger, actionCommandManager, cache);
    addBasicActionCommands(game);

    game->startGame(gameloop);

    game = nullptr;
    return 0;
}
