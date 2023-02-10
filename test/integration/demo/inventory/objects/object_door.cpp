#include "object_door.hpp"
#include "game_interface.hpp"

ObjectDoor::ObjectDoor(std::weak_ptr<TemperatureNode> node)
    : m_tempNode { node }
{
}

void ObjectDoor::doCreate()
{
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
void ObjectDoor::toggleDoor() { m_closed = !m_closed; }
bool ObjectDoor::getIsOpen() const { return !m_closed; }
