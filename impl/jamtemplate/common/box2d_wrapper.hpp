#include "Box2D/Box2D.h"
#include <cassert>

namespace jt {
/// Interface for box2World
class Box2DWorldInterface {
public:
    /// Create a physics body
    /// \param definition the definition describing the body
    /// \return the createdy body
    virtual b2Body* createBody(const b2BodyDef* definition) = 0;

    /// Destroy a physics body
    /// \param body pointer to the body to be destroyed
    virtual void destroyBody(b2Body* body) = 0;

    /// Destructor
    virtual ~Box2DWorldInterface() = default;
};

/// Implementation of the Box2DWorldInterface
class Box2DWorldWrapper : public Box2DWorldInterface {
public:
    Box2DWorldWrapper(const std::shared_ptr<b2World> world)
        : m_world { world }
    {
    }

    b2Body* createBody(const b2BodyDef* def) override
    {
        assert(!m_world.expired());
        return m_world.lock()->CreateBody(def);
    }

    void destroyBody(b2Body* body) override
    {
        if (m_world.expired()) {
            return;
        }
        m_world.lock()->DestroyBody(body);
    }

private:
    std::weak_ptr<b2World> m_world;
};
} // namespace jt
