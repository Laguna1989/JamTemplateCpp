#ifndef JAMTEMPLATE_BOX_2D_CONTACT_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_BOX_2D_CONTACT_MANAGER_INTERFACE_HPP
#include <box2dwrapper/box_2d_contact_callback_manager_interface.hpp>
#include <Box2D/Dynamics/b2WorldCallbacks.h>

namespace jt {
class Box2DContactManagerInterface : public Box2DContactCallbackManagerInterface,
                                     public b2ContactListener { };
} // namespace jt

#endif // JAMTEMPLATE_BOX_2D_CONTACT_MANAGER_INTERFACE_HPP
