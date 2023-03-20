#ifndef JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_REGISTRY_INTERFACE_HPP
#define JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_REGISTRY_INTERFACE_HPP

#include <box2dwrapper/box2d_contact_callback_interface.hpp>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class Box2DContactCallbackRegistryInterface {
public:
    /// Get the number of registered callbacks.
    /// \return the number of registered callbacks
    virtual std::size_t size() const = 0;

    /// Register a callback
    /// \param callbackIdentifier The identifier of the callback
    /// \param callback the actual callback to be invoked.
    virtual void registerCallback(std::string const& callbackIdentifier,
        std::shared_ptr<jt::Box2DContactCallbackInterface> callback)
        = 0;

    /// Unregister a callback.
    /// \param callbackIdentifier The identifier of the callback. If no callback with this
    /// identifier is registered, nothing happens.
    virtual void unregisterCallback(std::string const& callbackIdentifier) = 0;

    /// Get a vector of all identifier strings.
    /// \return the vector of identifiers.
    virtual std::vector<std::string> getAllCallbackIdentifiers() const = 0;

    virtual ~Box2DContactCallbackRegistryInterface() = default;

    // no copy, no move
    Box2DContactCallbackRegistryInterface(const Box2DContactCallbackRegistryInterface&) = delete;
    Box2DContactCallbackRegistryInterface(Box2DContactCallbackRegistryInterface&&) = delete;
    Box2DContactCallbackRegistryInterface& operator=(const Box2DContactCallbackRegistryInterface&)
        = delete;
    Box2DContactCallbackRegistryInterface& operator=(Box2DContactCallbackRegistryInterface&&)
        = delete;

protected:
    // default constructor can only be called from derived classes
    Box2DContactCallbackRegistryInterface() = default;
};

} // namespace jt
#endif // JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_REGISTRY_INTERFACE_HPP
