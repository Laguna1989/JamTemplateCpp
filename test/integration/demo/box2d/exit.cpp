#include "exit.hpp"
#include "math_helper.hpp"
#include <game_interface.hpp>

Exit::Exit(jt::tilemap::InfoRect const& rect) { m_info = rect; }

void Exit::doCreate()
{
    m_sprite
        = std::make_shared<jt::Sprite>("assets/test/integration/demo/exit.png", textureManager());

    m_sprite->setPosition(m_info.position);
}

void Exit::doUpdate(float const elapsed) { m_sprite->update(elapsed); }

void Exit::doDraw() const { m_sprite->draw(renderTarget()); }

void Exit::checkIfPlayerIsInExit(
    jt::Vector2f const& playerPosition, std::function<void(std::string const&)> callback)
{
    jt::Rectf const exitRect { m_info.position.x, m_info.position.y, m_info.size.x, m_info.size.y };
    if (jt::MathHelper::checkIsIn(exitRect, playerPosition)) {
        auto const nextLevelName = m_info.properties.strings["next_level"];
        getGame()->logger().info("switch to next level: " + nextLevelName, { "platformer" });
        callback(nextLevelName);
    }
}
