#ifndef JAMTEMPLATE_LOGGING_BOX2D_CONTACT_MANAGER_HPP
#define JAMTEMPLATE_LOGGING_BOX2D_CONTACT_MANAGER_HPP

#include <box2dwrapper/box2d_contact_manager_interface.hpp>
#include <log/logger_interface.hpp>
namespace jt {

class LoggingBox2DContactManager : public jt::Box2DContactManagerInterface {
public:
    LoggingBox2DContactManager(
        std::shared_ptr<jt::Box2DContactManagerInterface> decoratee, jt::LoggerInterface& logger);

    size_t size() const override;
    void registerCallback(std::string const& callbackIdentifier,
        std::shared_ptr<jt::Box2DContactCallbackInterface> callback) override;
    void unregisterCallback(std::string const& callbackIdentifier) override;
    std::vector<std::string> getAllCallbackIdentifiers() const override;

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

private:
    std::shared_ptr<jt::Box2DContactManagerInterface> m_decoratee { nullptr };
    jt::LoggerInterface& m_logger;
};

} // namespace jt

#endif // JAMTEMPLATE_LOGGING_BOX2D_CONTACT_MANAGER_HPP
