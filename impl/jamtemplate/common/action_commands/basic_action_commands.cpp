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
                logger.lock()->action("invalid number of arguments for shake");
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
                logger.lock()->action("invalid number of arguments for reset");
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
                logger.lock()->action("invalid number of arguments for zoom");
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
                logger.lock()->action("invalid number of arguments for pos");
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
                logger.lock()->action("invalid number of arguments for move");
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

} // namespace

void jt::addBasicActionCommands(jt::GameBase& game)
{
    addCommandHelp(game);
    addCommandClear(game);
    addCommandsCam(game);

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

} // namespace jt
