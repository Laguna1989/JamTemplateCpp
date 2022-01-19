#include "basic_action_commands.hpp"
#include "game_base.hpp"
#include "math_helper.hpp"

namespace jt {
namespace {
void addCommandHelp(std::shared_ptr<GameBase>& game)
{
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand("help",
        [&mgr = game->getActionCommandManager(), &logger = game->getLogger()](auto /*args*/) {
            logger.action("Available commands:");
            for (auto& c : mgr.getAllCommands()) {
                logger.action(" - " + c);
            }
        }));
}

void addCommandClear(std::shared_ptr<GameBase>& game)
{
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "clear", [&logger = game->getLogger()](auto /*args*/) { logger.clear(); }));
}

void addCommandsCam(std::shared_ptr<GameBase>& game)
{
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "cam.shake", [&cam = game->gfx().camera(), &logger = game->getLogger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float duration = std::stof(args.at(0));
            float strength = std::stof(args.at(1));
            cam.shake(duration, strength);
        }));
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "cam.reset", [&cam = game->gfx().camera(), &logger = game->getLogger()](auto args) {
            if (args.size() != 0) {
                logger.error("invalid number of arguments");
                return;
            }
            cam.reset();
        }));
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "cam.zoom", [&cam = game->gfx().camera(), &logger = game->getLogger()](auto args) {
            if (args.size() != 1) {
                logger.error("invalid number of arguments");
                return;
            }
            float zoom = std::stof(args.at(0));

            cam.setZoom(zoom);
        }));
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "cam.pos", [&cam = game->gfx().camera(), &logger = game->getLogger()](auto args) {
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
    game->storeActionCommand(game->getActionCommandManager().registerTemporaryCommand(
        "cam.move", [&cam = game->gfx().camera(), &logger = game->getLogger()](auto args) {
            if (args.size() != 2) {
                logger.error("invalid number of arguments");
                return;
            }
            float x = std::stof(args.at(0));
            float y = std::stof(args.at(1));
            cam.move(Vector2f { x, y });
        }));
}

void addCommandTextureManager(std::shared_ptr<GameBase>& game)
{
    game->storeActionCommand(
        game->getActionCommandManager().registerTemporaryCommand("textureManagerInfo",
            [&logger = game->getLogger(), &textureManager = game->gfx().textureManager()](
                auto /*args*/) {
                logger.action(
                    "stored textures: " + std::to_string(textureManager.getNumberOfTextures()));
            }));
}

void addCommandsMusicPlayer(std::shared_ptr<GameBase>& game)
{

    // TODO create new commands for new afx interface
}

} // namespace

void addBasicActionCommands(std::shared_ptr<GameBase>& game)
{
    addCommandHelp(game);
    addCommandClear(game);
    addCommandsCam(game);
    addCommandTextureManager(game);
    addCommandsMusicPlayer(game);
}

} // namespace jt
