#include "box2d_contact_manager.hpp"
#include <algorithm>
#include <iterator>

std::size_t jt::Box2DContactManager::size() const { return m_callbacks.size(); }

void jt::Box2DContactManager::registerCallback(
    std::string const& callbackIdentifier, std::shared_ptr<Box2DContactCallbackInterface> callback)
{
    m_callbacks[callbackIdentifier] = callback;
}

void jt::Box2DContactManager::unregisterCallback(std::string const& callbackIdentifier)
{
    m_callbacks.erase(callbackIdentifier);
}

void jt::Box2DContactManager::BeginContact(b2Contact* contact)
{
    for (auto const& kvp : m_callbacks) {
        if (kvp.second) [[likely]] {
            if (kvp.second->getEnabled()) {
                kvp.second->onBeginContact(contact);
            }
        }
    }
}

void jt::Box2DContactManager::EndContact(b2Contact* contact)
{
    for (auto const& kvp : m_callbacks) {
        if (kvp.second) [[likely]] {
            if (kvp.second->getEnabled()) {
                kvp.second->onEndContact(contact);
            }
        }
    }
}

std::vector<std::string> jt::Box2DContactManager::getAllCallbackIdentifiers() const
{
    std::vector<std::string> identifiers;
    std::transform(m_callbacks.begin(), m_callbacks.end(), std::back_inserter(identifiers),
        [](auto kvp) { return kvp.first; });
    return identifiers;
}
