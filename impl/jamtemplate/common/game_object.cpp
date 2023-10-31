#include "game_object.hpp"
#include <game_interface.hpp>
#include <system_helper.hpp>
#include <memory>
#include <stdexcept>

void jt::GameObject::create()
{
    checkForValidGame();
    doCreate();
}

void jt::GameObject::checkForValidGame() const
{
    if (m_game.expired()) {
        throw std::logic_error { "ERROR: Cannot jt::GameObject::getGame():  m_game expired!" };
    }
}

void jt::GameObject::update(float const elapsed)
{
    m_age += elapsed;
    doUpdate(elapsed);
}

void jt::GameObject::draw() const { doDraw(); };

float jt::GameObject::getAge() const { return m_age; }

void jt::GameObject::setGameInstance(std::weak_ptr<jt::GameInterface> gameInstance)
{
    if (!jt::SystemHelper::is_uninitialized_weak_ptr(m_game)) {
        throw std::logic_error {
            "It is not allowed to call setGameInstance twice on a GameObject."
        };
    }
    m_game = std::move(gameInstance);
}

std::shared_ptr<jt::GameInterface> jt::GameObject::getGame()
{
    if (m_game.expired()) {
        throw std::logic_error { "ERROR: Cannot jt::GameObject::getGame():  m_game expired!" };
    }
    return m_game.lock();
}

std::shared_ptr<jt::GameInterface> jt::GameObject::getGame() const
{
    checkForValidGame();
    return m_game.lock();
}

void jt::GameObject::kill()
{
    m_alive = false;
    doKill();
}

bool jt::GameObject::isAlive() const { return m_alive; }

void jt::GameObject::destroy() { doDestroy(); }

void jt::GameObject::doUpdate(float const /*elapsed*/) {};
void jt::GameObject::doDraw() const {};
void jt::GameObject::doCreate() {};
void jt::GameObject::doKill() {};
void jt::GameObject::doDestroy() {};

void jt::GameObject::storeActionCommand(std::shared_ptr<void> commandCallback)
{
    m_storedActionCommands.emplace_back(std::move(commandCallback));
}

std::string jt::GameObject::getName() const { return ""; }
std::size_t jt::GameObject::getNumberOfAliveGameObjects() const { return aliveObjects(); }
std::size_t jt::GameObject::getNumberOfCreatedGameObjects() const { return createdObjects(); }

jt::TextureManagerInterface& jt::GameObject::textureManager() const
{
    return getGame()->gfx().textureManager();
}

std::shared_ptr<jt::RenderTargetInterface> jt::GameObject::renderTarget() const
{
    return getGame()->gfx().target();
}
std::shared_ptr<jt::KeyboardInterface> jt::GameObject::keyboard() const
{
    return getGame()->input().keyboard();
}
std::shared_ptr<jt::MouseInterface> jt::GameObject::mouse() const
{
    return getGame()->input().mouse();
}
