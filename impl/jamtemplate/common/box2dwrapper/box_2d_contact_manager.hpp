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
class Box2DContactManager : public b2ContactListener {
public:
    std::size_t size() const;
    void registerCallback(std::string const& callbackIdentifier,
        std::shared_ptr<Box2DContactCallbackInterface> callback);
    void unregisterCallback(std::string const& callbackIdentifier);

    std::vector<std::string> getAllCallbackIdentifiers() const;

    // callbacks for b2ContactListener
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

private:
    std::map<std::string, std::shared_ptr<Box2DContactCallbackInterface>> m_callbacks;
};
} // namespace jt
#endif // JAMTEMPLATE_BOX_2_D_CONTACT_MANAGER_HPP
