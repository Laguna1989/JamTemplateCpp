
#include "contact_listener_player_grounded.hpp"
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <iostream>

void ContactListenerPlayerGrounded::BeginContact(b2Contact* contact)
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
    //    std::cout << "start contact: " << m_numberOfFeetContacts << std::endl;

    p->setTouchesGround(m_numberOfFeetContacts >= 1);
}

void ContactListenerPlayerGrounded::EndContact(b2Contact* contact)
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
    //    std::cout << "end contact: " << m_numberOfFeetContacts << std::endl;
    p->setTouchesGround(m_numberOfFeetContacts >= 1);
}
void ContactListenerPlayerGrounded::setPlayer(std::weak_ptr<Player> player) { m_player = player; }
bool ContactListenerPlayerGrounded::isPlayerFeetFixture(b2Fixture* fa) const
{
    void* fixtureUserData = fa->GetUserData();
    return (std::uint64_t)fixtureUserData == 3U;
}
