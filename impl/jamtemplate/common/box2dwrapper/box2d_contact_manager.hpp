#ifndef JAMTEMPLATE_BOX2D_CONTACT_MANAGER_HPP
#define JAMTEMPLATE_BOX2D_CONTACT_MANAGER_HPP

#include <box2dwrapper/box2d_contact_manager_interface.hpp>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {
class Box2DContactManager : public jt::Box2DContactManagerInterface {
public:
    std::size_t size() const override;
    void registerCallback(std::string const& callbackIdentifier,
        std::shared_ptr<Box2DContactCallbackInterface> callback) override;

    void unregisterCallback(std::string const& callbackIdentifier) override;

    std::vector<std::string> getAllCallbackIdentifiers() const override;

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
#endif // JAMTEMPLATE_BOX2D_CONTACT_MANAGER_HPP
