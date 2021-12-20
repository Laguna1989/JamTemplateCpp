#ifndef GUARD_JAMTEMAPLTE_ACTOR_HPP
#define GUARD_JAMTEMAPLTE_ACTOR_HPP

#include "game_object.hpp"
#include "pathfinder/node_interface.hpp"
#include "sprite.hpp"

class Actor : public ::jt::GameObject {
public:
    void setPosition(jt::Vector2u const& posInTiles);
    jt::Vector2f getPosition() const;

    void setPath(std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> const& path);

    jt::Vector2f getFinalPosition();

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::shared_ptr<jt::Sprite> m_sprite;

    std::vector<std::weak_ptr<jt::pathfinder::NodeInterface>> m_path;
    void walkAlongPath(float const elapsed);

    float m_walkTimerCurrent { 0.0f };
    float m_walkTimerMax { 0.5f };
    void removeDuplicatesFromPath();
};

#endif // GUARD_JAMTEMAPLTE_ACTOR_HPP
