#ifndef DEMO_SCENE_BOX2D_QUERIES_HPP
#define DEMO_SCENE_BOX2D_QUERIES_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <collision/physics_body.hpp>
#include <game_object.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <text.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

/// Bouncing Box2D bodies. Contacts flash the bodies, the rotatable quad around the mouse is a
/// shape overlap query and the line from the bottom of the screen towards the mouse is a ray cast.
class SceneBox2DQueries : public jt::GameObject {
public:
    std::string getName() const override;

private:
    // declared first so that it is destroyed last
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };
    std::vector<std::shared_ptr<jt::Box2DObject>> m_walls {};
    // shared_ptr: the body user data points to the PhysicsBody, so its address must be stable
    std::vector<std::shared_ptr<PhysicsBody>> m_bodies {};

    std::vector<PhysicsBody*> m_queryHits {};
    float m_queryRotation { 0.0f }; // degrees
    PhysicsBody* m_rayHit { nullptr };
    jt::Vector2f m_rayEnd {};

    std::shared_ptr<jt::Shape> m_queryShape { nullptr };
    std::shared_ptr<jt::Line> m_rayLine { nullptr };
    std::shared_ptr<jt::Shape> m_rayHitMarker { nullptr };
    std::shared_ptr<jt::Text> m_info { nullptr };

    void doCreate() override;
    void doUpdate(float elapsed) override;
    void doDraw() const override;

    void createWall(jt::Vector2f const& center, jt::Vector2f const& halfSize);
    void createBody(jt::Vector2f const& position);

    void flashContacts();
    void queryQuad(jt::Vector2f const& center);
    void castRay(jt::Vector2f const& target);
    void updateBodies(float elapsed);
};

#endif // DEMO_SCENE_BOX2D_QUERIES_HPP
