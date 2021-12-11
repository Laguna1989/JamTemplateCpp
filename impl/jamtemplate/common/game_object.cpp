#include "game_object.hpp"
#include "game_interface.hpp"
#include "system_helper.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace jt {
void GameObject::create()
{
    try {
        auto const g = getGame();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::logic_error { "Gameobject cannot be created without gameinstace being set." };
    }
    doCreate();
}

void GameObject::update(float const elapsed)
{
    m_age += elapsed;
    doUpdate(elapsed);
}

void GameObject::draw() const { doDraw(); };

float GameObject::getAge() const { return m_age; }
void GameObject::setAge(float newAgeInSeconds) { m_age = newAgeInSeconds; }

void GameObject::setGameInstance(std::weak_ptr<GameInterface> gameInstance)
{
    if (!jt::SystemHelper::is_uninitialized_weak_ptr(m_game)) {
        throw std::logic_error {
            "It is not allowed to call setGameInstance twice on a GameObject."
        };
    }
    m_game = std::move(gameInstance);
}

std::shared_ptr<GameInterface> GameObject::getGame()
{
    if (m_game.expired()) {
        throw std::logic_error { "ERROR: Cannot GameObject::getGame():  m_game expired!" };
    }
    return m_game.lock();
}

std::shared_ptr<GameInterface> GameObject::getGame() const
{
    if (m_game.expired()) {
        throw std::logic_error { "ERROR: Cannot GameObject::getGame():  m_game expired!" };
    }
    return m_game.lock();
}

void GameObject::kill()
{
    m_alive = false;
    doKill();
}

bool GameObject::isAlive() const { return m_alive; }

void GameObject::destroy() { doDestroy(); }

void GameObject::doUpdate(float const /*elapsed*/) {};
void GameObject::doDraw() const {};
void GameObject::doCreate() {};
void GameObject::doKill() {};
void GameObject::doDestroy() {};

void GameObject::storeActionCommand(std::shared_ptr<void> commandCallback)
{
    m_storedActionCommands.emplace_back(std::move(commandCallback));
}
std::string GameObject::getName() const { return ""; }

} // namespace jt
