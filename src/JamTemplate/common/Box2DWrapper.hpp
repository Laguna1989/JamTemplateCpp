#include "Box2D/Box2D.h"
#include <cassert>

namespace jt {
class Box2DWorldInterface {
public:
    virtual b2Body* CreateBody(const b2BodyDef* def) = 0;
    virtual void DestroyBody(b2Body* body) = 0;
};

class Box2DWorldWrapper : public Box2DWorldInterface {
public:
    Box2DWorldWrapper(const std::shared_ptr<b2World> world)
        : m_world { world }
    {
    }

    b2Body* CreateBody(const b2BodyDef* def) override
    {
        assert(!m_world.expired());
        return m_world.lock()->CreateBody(def);
    }

    void DestroyBody(b2Body* body) override
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
