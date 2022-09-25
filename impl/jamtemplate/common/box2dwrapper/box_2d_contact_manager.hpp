#ifndef JAMTEMPLATE_BOX_2_D_CONTACT_MANAGER_HPP
#define JAMTEMPLATE_BOX_2_D_CONTACT_MANAGER_HPP

#include <box2dwrapper/box_2d_contact_callback_interface.hpp>
#include <Box2D/Box2D.h>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {
// TODO create interface for Box2DContactManager and make this an implementation of the interface
class Box2DContactManager : public b2ContactListener {
public:
    /// Get the number of registered callbacks.
    /// \return the number of registered callbacks
    std::size_t size() const;

    /// Register a callback
    /// \param callbackIdentifier The identifier of the callback
    /// \param callback the actual callback to be invoked.
    void registerCallback(std::string const& callbackIdentifier,
        std::shared_ptr<Box2DContactCallbackInterface> callback);

    /// Unregister a callback.
    /// \param callbackIdentifier The identifier of the callback. If no callback with this
    /// identifier is registered, nothing happens.
    void unregisterCallback(std::string const& callbackIdentifier);

    /// Get a vector of all identifier strings.
    /// \return the vector of identifiers.
    std::vector<std::string> getAllCallbackIdentifiers() const;

    // callbacks for b2ContactListener
    /// Do not call this manually
    /// \param contact
    void BeginContact(b2Contact* contact) override;
    /// Do not call this manually
    /// \param contact
    void EndContact(b2Contact* contact) override;

private:
    std::map<std::string, std::shared_ptr<Box2DContactCallbackInterface>> m_callbacks;
};
} // namespace jt
#endif // JAMTEMPLATE_BOX_2_D_CONTACT_MANAGER_HPP
