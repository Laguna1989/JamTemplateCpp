#include "basic_action_commands.hpp"
#include "game_base.hpp"
#include "math_helper.hpp"

namespace jt {
namespace {
void addCommandHelp(jt::GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("help",
        [mgr = std::weak_ptr<ActionCommandManagerInterface> { game.getActionCommandManager() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            logger.lock()->action("Available commands:");
            if (mgr.expired()) {
                return;
            }
            for (auto& c : mgr.lock()->getAllCommands()) {
                logger.lock()->action(" - " + c);
            }
        }));
}

void addCommandClear(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "clear", [logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            logger.lock()->clear();
        }));
}

void addCommandsCam(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("cam.shake",
        [cam = std::weak_ptr<CamInterface> { game.getCamera() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto args) {
            if (args.size() != 2) {
                if (logger.expired()) {
                    return;
                }
                logger.lock()->error("invalid number of arguments");
                return;
            }
            float duration = std::stof(args.at(0));
            float strength = std::stof(args.at(1));
            if (cam.expired()) {
                return;
            }
            cam.lock()->shake(duration, strength);
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("cam.reset",
        [cam = std::weak_ptr<CamInterface> { game.getCamera() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto args) {
            if (args.size() != 0) {
                if (logger.expired()) {
                    return;
                }
                logger.lock()->error("invalid number of arguments");
                return;
            }
            if (cam.expired()) {
                return;
            }
            cam.lock()->reset();
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("cam.zoom",
        [cam = std::weak_ptr<CamInterface> { game.getCamera() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto args) {
            if (args.size() != 1) {
                if (logger.expired()) {
                    return;
                }
                logger.lock()->error("invalid number of arguments");
                return;
            }
            float zoom = std::stof(args.at(0));
            if (cam.expired()) {
                return;
            }
            cam.lock()->setZoom(zoom);
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("cam.pos",
        [cam = std::weak_ptr<CamInterface> { game.getCamera() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto args) {
            if (args.size() != 2 && args.size() != 0) {
                if (logger.expired()) {
                    return;
                }
                logger.lock()->error("invalid number of arguments");
                return;
            }
            if (cam.expired()) {
                return;
            }

            if (args.size() == 0) {
                auto const p = cam.lock()->getCamOffset();
                logger.lock()->action(jt::MathHelper::floatToStringWithXDigits(p.x, 2) + " "
                    + jt::MathHelper::floatToStringWithXDigits(p.y, 2));
            } else {
                float x = std::stof(args.at(0));
                float y = std::stof(args.at(1));

                cam.lock()->setCamOffset(Vector2f { x, y });
            }
        }));
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("cam.move",
        [cam = std::weak_ptr<CamInterface> { game.getCamera() },
            logger = std::weak_ptr<LoggerInterface> { game.getLogger() }](auto args) {
            if (args.size() != 2) {
                if (logger.expired()) {
                    return;
                }
                logger.lock()->error("invalid number of arguments");
                return;
            }
            float x = std::stof(args.at(0));
            float y = std::stof(args.at(1));
            if (cam.expired()) {
                return;
            }
            cam.lock()->move(Vector2f { x, y });
        }));
}

void addCommandTextureManager(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand(
        "textureManagerInfo",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            textureManager = std::weak_ptr<TextureManagerInterface> { game.getTextureManager() }](
            auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            if (textureManager.expired()) {
                return;
            }
            logger.lock()->action(
                "stored textures: " + std::to_string(textureManager.lock()->getNumberOfTextures()));
        }));
}

void addCommandsMusicPlayer(GameBase& game)
{
    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("music.stop",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            player = std::weak_ptr<MusicPlayerInterface> { game.getMusicPlayer() }](auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            if (player.expired()) {
                return;
            }
            player.lock()->stopMusic();
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("music.mute",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            player = std::weak_ptr<MusicPlayerInterface> { game.getMusicPlayer() }](auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            if (player.expired()) {
                return;
            }
            player.lock()->setMusicVolume(0);
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("music.volume",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            player = std::weak_ptr<MusicPlayerInterface> { game.getMusicPlayer() }](auto args) {
            if (logger.expired()) {
                return;
            }
            if (player.expired()) {
                return;
            }
            if (args.size() == 0) {
                logger.lock()->action("current volume: "
                    + jt::MathHelper::floatToStringWithXDigits(player.lock()->getMusicVolume(), 2));
            } else if (args.size() == 1) {
                auto volume = std::stof(args.at(0));
                volume = jt::MathHelper::clamp(volume, 0.0f, 100.0f);
                player.lock()->setMusicVolume(volume);
            } else {
                logger.lock()->error("invalid number of arguments");
            }
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("music.play",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            player = std::weak_ptr<MusicPlayerInterface> { game.getMusicPlayer() }](auto args) {
            if (logger.expired()) {
                return;
            }
            if (player.expired()) {
                return;
            }
            if (args.size() == 1) {
                auto track = args.at(0);
                player.lock()->playMusic(track);
            } else {
                logger.lock()->error("invalid number of arguments");
            }
        }));

    game.storeActionCommand(game.getActionCommandManager()->registerTemporaryCommand("music.file",
        [logger = std::weak_ptr<LoggerInterface> { game.getLogger() },
            player = std::weak_ptr<MusicPlayerInterface> { game.getMusicPlayer() }](auto /*args*/) {
            if (logger.expired()) {
                return;
            }
            if (player.expired()) {
                return;
            }
            auto const file = player.lock()->getMusicFilePath();
            logger.lock()->action("currently playing: '" + file + "'");
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
