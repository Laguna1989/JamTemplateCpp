#ifndef JAMTEMPLATE_MY_CONTACT_LISTENER_HPP
#define JAMTEMPLATE_MY_CONTACT_LISTENER_HPP

#include "PlatformPlayer.hpp"
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <memory>

class MyContactListener : public b2ContactListener {
public:
    void setPlayer(std::weak_ptr<Player> player);

private:
    std::weak_ptr<Player> m_player;
    int m_numberOfFeetContacts { 0 };

    /// Called when two fixtures begin to touch.
    void BeginContact(b2Contact* contact) override;

    /// Called when two fixtures cease to touch.
    void EndContact(b2Contact* contact) override;

    bool isPlayerFeetFixture(b2Fixture* fa) const;
};

#endif // JAMTEMPLATE_MY_CONTACT_LISTENER_HPP
