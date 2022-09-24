
#ifndef JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP
#define JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP

#include <Box2D/Box2D.h>

namespace jt {
class Box2DContactCallbackInterface {
public:
    virtual ~Box2DContactCallbackInterface() = default;

    virtual void onBeginContact(b2Contact* contact) = 0;
    virtual void onEndContact(b2Contact* contact) = 0;

    virtual void setEnabled(bool enabled) = 0;
    virtual bool getEnabled() const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_BOX_2D_CONTACT_CALLBACK_INTERFACE_HPP
