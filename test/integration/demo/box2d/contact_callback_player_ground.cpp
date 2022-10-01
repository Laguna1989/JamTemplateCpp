
#include "contact_callback_player_ground.hpp"
#include <box2d/user_data_entries.hpp>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <iostream>

void ContactCallbackPlayerGround::onBeginContact(b2Contact* contact)
{
    auto p = m_player.lock();
    if (!p) {
        return;
    }
    auto const fa = contact->GetFixtureA();
    auto const fb = contact->GetFixtureB();

    if (isPlayerFeetFixture(fa) || isPlayerFeetFixture(fb)) {
        m_numberOfFeetContacts++;
    }
    p->setTouchesGround(m_numberOfFeetContacts >= 1);
}

void ContactCallbackPlayerGround::onEndContact(b2Contact* contact)
{
    auto p = m_player.lock();
    if (!p) {
        return;
    }
    auto const fa = contact->GetFixtureA();
    auto const fb = contact->GetFixtureB();

    if (isPlayerFeetFixture(fa) || isPlayerFeetFixture(fb)) {
        m_numberOfFeetContacts--;
    }
    p->setTouchesGround(m_numberOfFeetContacts >= 1);
}
void ContactCallbackPlayerGround::setPlayer(std::weak_ptr<Player> player) { m_player = player; }
bool ContactCallbackPlayerGround::isPlayerFeetFixture(b2Fixture* fa) const
{
    void* fixtureUserData = fa->GetUserData();
    return (std::uint64_t)fixtureUserData == g_userDataPlayerFeetID;
}
void ContactCallbackPlayerGround::setEnabled(bool enabled) { m_enabled = enabled; }
bool ContactCallbackPlayerGround::getEnabled() const { return true; }
