#include "logging_box2d_contact_manager.hpp"
#include <stdexcept>

jt::LoggingBox2DContactManager::LoggingBox2DContactManager(
    std::shared_ptr<jt::Box2DContactManagerInterface> decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
    if (m_decoratee == nullptr) {
        m_logger.fatal(
            "LoggingBox2DContactManager instantiated with nullptr decoratee", { "jt", "box2d" });
        throw std::invalid_argument {
            "LoggingBox2DContactManager instantiated with nullptr decoratee"
        };
    }
    m_logger.info("Box2DContactManager created", { "jt", "box2d" });
}

size_t jt::LoggingBox2DContactManager::size() const
{
    auto const size = m_decoratee->size();
    m_logger.verbose(
        "Box2DContactManager.size() called: " + std::to_string(size), { "jt", "box2d" });

    return size;
}

void jt::LoggingBox2DContactManager::registerCallback(std::string const& callbackIdentifier,
    std::shared_ptr<jt::Box2DContactCallbackInterface> callback)
{
    m_logger.info(
        "Box2DContactManager register '" + callbackIdentifier + "' callback", { "jt", "box2d" });
    m_decoratee->registerCallback(callbackIdentifier, callback);
}

void jt::LoggingBox2DContactManager::unregisterCallback(std::string const& callbackIdentifier)
{
    m_logger.info(
        "Box2DContactManager unregister '" + callbackIdentifier + "' callback", { "jt", "box2d" });
    m_decoratee->unregisterCallback(callbackIdentifier);
}

std::vector<std::string> jt::LoggingBox2DContactManager::getAllCallbackIdentifiers() const
{
    m_logger.verbose("Box2DContactManager getAllCallbackIdentifiers", { "jt", "box2d" });
    return m_decoratee->getAllCallbackIdentifiers();
}
void jt::LoggingBox2DContactManager::BeginContact(b2Contact* contact)
{
    m_logger.debug("Box2DContactManager BeginContact", { "jt", "box2d" });
    m_decoratee->BeginContact(contact);
}
void jt::LoggingBox2DContactManager::EndContact(b2Contact* contact)
{
    m_logger.debug("Box2DContactManager EndContact", { "jt", "box2d" });
    m_decoratee->EndContact(contact);
}
