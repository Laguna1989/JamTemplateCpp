#include "basic_action_commands.hpp"
#include <game_base.hpp>
#include <math_helper.hpp>

namespace {
void addCommandHelp(std::shared_ptr<jt::GameBase>& game)
{
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "help", [&mgr = game->actionCommandManager(), &logger = game->logger()](auto /*args*/) {
            logger.action("Available commands:");
            for (auto const& c : mgr.getAllCommands()) {
                logger.action(" - " + c);
            }
        }));
}

void addCommandClear(std::shared_ptr<jt::GameBase>& game)
{
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "clear", [history = game->cache().getLogHistory()](auto /*args*/) { history->clear(); }));
}

void addCommandsCam(std::shared_ptr<jt::GameBase>& game)
{
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "cam.shake", [&cam = game->gfx().camera(), &logger = game->logger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float duration = std::stof(args.at(0));
            float strength = std::stof(args.at(1));
            cam.shake(duration, strength);
        }));
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "cam.reset", [&cam = game->gfx().camera(), &logger = game->logger()](auto args) {
            if (args.size() != 0) {
                logger.error("invalid number of arguments");
                return;
            }
            cam.reset();
        }));
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "cam.zoom", [&cam = game->gfx().camera(), &logger = game->logger()](auto args) {
            if (args.size() != 1) {
                logger.error("invalid number of arguments");
                return;
            }
            float zoom = std::stof(args.at(0));

            cam.setZoom(zoom);
        }));
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "cam.pos", [&cam = game->gfx().camera(), &logger = game->logger()](auto args) {
            if (args.size() != 2 && args.size() != 0) {
                logger.error("invalid number of arguments");
                return;
            }

            if (args.size() == 0) {
                auto const p = cam.getCamOffset();
                logger.action(jt::MathHelper::floatToStringWithXDecimalDigits(p.x, 2) + " "
                    + jt::MathHelper::floatToStringWithXDecimalDigits(p.y, 2));
            } else {
                float x = std::stof(args.at(0));
                float y = std::stof(args.at(1));

                cam.setCamOffset(jt::Vector2f { x, y });
            }
        }));
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "cam.move", [&cam = game->gfx().camera(), &logger = game->logger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float x = std::stof(args.at(0));
            float y = std::stof(args.at(1));
            cam.move(jt::Vector2f { x, y });
        }));
}

void addCommandTextureManager(std::shared_ptr<jt::GameBase>& game)
{
    game->storeActionCommand(game->actionCommandManager().registerTemporaryCommand(
        "textureManagerInfo",
        [&logger = game->logger(), &textureManager = game->gfx().textureManager()](auto /*args*/) {
            logger.action(
                "stored textures: " + std::to_string(textureManager.getNumberOfTextures()));
        }));
}

void addCommandsMusicPlayer(std::shared_ptr<jt::GameBase>& /*game*/)
{
    // TODO
}

} // namespace

void jt::addBasicActionCommands(std::shared_ptr<jt::GameBase> game)
{
    addCommandHelp(game);
    addCommandClear(game);
    addCommandsCam(game);
    addCommandTextureManager(game);
    addCommandsMusicPlayer(game);
}
