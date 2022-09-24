#ifndef JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP
#define JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP

#include <Box2D/Box2D.h>

namespace jt {
class Box2DContactCallbackInterface {
public:
    virtual ~Box2DContactCallbackInterface() = default;

    /// Will be invoked when a two bodies start to be into contact.
    /// \param contact the box2d contact information
    virtual void onBeginContact(b2Contact* contact) = 0;

    /// Will be invoked when two bodies stop to be in contact.
    /// \param contact te box2d contact information
    virtual void onEndContact(b2Contact* contact) = 0;

    /// Enable the callback. Disabled callbacks are ignored by the ContactManager
    /// \param enabled
    virtual void setEnabled(bool enabled) = 0;
    /// Get if the callback is enabled
    /// \return true if enabled, false otherwise.
    virtual bool getEnabled() const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP
