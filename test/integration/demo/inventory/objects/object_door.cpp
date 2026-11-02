#include "object_door.hpp"
#include <game_interface.hpp>

ObjectDoor::ObjectDoor(
    std::weak_ptr<TemperatureNode> node, std::shared_ptr<jt::Box2DWorldInterface> world)
    : m_tempNode { node }
{
    auto bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    auto const pos = m_tempNode.lock()->getPosition();
    bodyDef.position = b2Vec2 { pos.x + 12, pos.y + 12 };
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, bodyDef);
}

void ObjectDoor::doCreate()
{
    auto shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.2f;
    auto const boxCollider = b2MakeBox(12.0f, 12.0f);
    b2CreatePolygonShape(m_physicsObject->getBodyId(), &shapeDef, &boxCollider);

    m_anim = std::make_shared<jt::Animation>();
    m_anim->add("assets/test/integration/demo/door.png", "open", jt::Vector2u { 24, 24 }, { 0u },
        0.1f, textureManager());
    m_anim->add("assets/test/integration/demo/door.png", "closed", jt::Vector2u { 24, 24 }, { 3u },
        0.1f, textureManager());

    m_anim->setPosition(m_tempNode.lock()->getPosition());
}
void ObjectDoor::doUpdate(float const elapsed)
{
    auto door = m_tempNode.lock();
    if (m_closed) {
        door->setInflow(m_inflowClosed);
        door->setThroughputFactor(0.0f);
        m_anim->play("closed");
    } else {
        door->setInflow(m_inflowOpen);
        door->setThroughputFactor(0.85f);
        m_anim->play("open");
    }
    m_anim->update(elapsed);
}
void ObjectDoor::doDraw() const { m_anim->draw(renderTarget()); }
void ObjectDoor::toggleDoor()
{
    m_closed = !m_closed;
    m_physicsObject->setEnabled(m_closed);
    // TODO modify pathfinding
}
bool ObjectDoor::getIsOpen() const { return !m_closed; }
std::string ObjectDoor::getDoorName() const { return m_name; }
void ObjectDoor::setDoorName(std::string const& name) { m_name = name; }
