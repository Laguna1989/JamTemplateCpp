#include "basic_action_commands.hpp"
#include "game_base.hpp"
#include "math_helper.hpp"

namespace jt {
namespace {
void addCommandHelp(jt::GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("help",
        [mgr = std::weak_ptr<ActionCommandManagerInterface> { game.getActionCommandManager() },
            &logger = game.getLogger()](auto /*args*/) {
            logger.action("Available commands:");
            if (mgr.expired()) {
                return;
            }
            for (auto& c : mgr.lock()->getAllCommands()) {
                logger.action(" - " + c);
            }
        }));
}

void addCommandClear(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "clear", [&logger = game.getLogger()](auto /*args*/) { logger.clear(); }));
}

void addCommandsCam(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "cam.shake", [&cam = game.getCamera(), &logger = game.getLogger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float duration = std::stof(args.at(0));
            float strength = std::stof(args.at(1));
            cam.shake(duration, strength);
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "cam.reset", [&cam = game.getCamera(), &logger = game.getLogger()](auto args) {
            if (args.size() != 0) {
                logger.error("invalid number of arguments");
                return;
            }
            cam.reset();
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "cam.zoom", [&cam = game.getCamera(), &logger = game.getLogger()](auto args) {
            if (args.size() != 1) {
                logger.error("invalid number of arguments");
                return;
            }
            float zoom = std::stof(args.at(0));

            cam.setZoom(zoom);
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "cam.pos", [&cam = game.getCamera(), &logger = game.getLogger()](auto args) {
            if (args.size() != 2 && args.size() != 0) {
                logger.error("invalid number of arguments");
                return;
            }

            if (args.size() == 0) {
                auto const p = cam.getCamOffset();
                logger.action(jt::MathHelper::floatToStringWithXDigits(p.x, 2) + " "
                    + jt::MathHelper::floatToStringWithXDigits(p.y, 2));
            } else {
                float x = std::stof(args.at(0));
                float y = std::stof(args.at(1));

                cam.setCamOffset(Vector2f { x, y });
            }
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "cam.move", [&cam = game.getCamera(), &logger = game.getLogger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float x = std::stof(args.at(0));
            float y = std::stof(args.at(1));
            cam.move(Vector2f { x, y });
        }));
}

void addCommandTextureManager(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "textureManagerInfo",
        [&logger = game.getLogger(),
            textureManager = std::weak_ptr<TextureManagerInterface> { game.getTextureManager() }](
            auto /*args*/) {
            if (textureManager.expired()) {
                return;
            }
            logger.action(
                "stored textures: " + std::to_string(textureManager.lock()->getNumberOfTextures()));
        }));
}

void addCommandsMusicPlayer(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "music.stop", [&logger = game.getLogger(), &player = game.getMusicPlayer()](auto /*args*/) {
            player.stopMusic();
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "music.mute", [&logger = game.getLogger(), &player = game.getMusicPlayer()](auto /*args*/) {
            player.setMusicVolume(0);
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "music.volume", [&logger = game.getLogger(), &player = game.getMusicPlayer()](auto args) {
            if (args.size() == 0) {
                logger.action("current volume: "
                    + jt::MathHelper::floatToStringWithXDigits(player.getMusicVolume(), 2));
            } else if (args.size() == 1) {
                auto volume = std::stof(args.at(0));
                volume = jt::MathHelper::clamp(volume, 0.0f, 100.0f);
                player.setMusicVolume(volume);
            } else {
                logger.error("invalid number of arguments");
            }
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "music.play", [&logger = game.getLogger(), &player = game.getMusicPlayer()](auto args) {
            if (args.size() == 1) {
                auto track = args.at(0);
                player.playMusic(track);
            } else {
                logger.error("invalid number of arguments");
            }
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "music.file", [&logger = game.getLogger(), &player = game.getMusicPlayer()](auto /*args*/) {
            auto const file = player.getMusicFilePath();
            logger.action("currently playing: '" + file + "'");
        }));
}

} // namespace

void addBasicActionCommands(jt::GameBase& game)
{
    addCommandHelp(game);
    addCommandClear(game);
    addCommandsCam(game);
    addCommandTextureManager(game);
    addCommandsMusicPlayer(game);
}

} // namespace jt
