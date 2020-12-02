#ifndef GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>

namespace jt {
// forward declaration
class GameBase;

class GameObject {
public:
    using Sptr = std::shared_ptr<GameObject>;

    GameObject() = default;

    virtual ~GameObject() = default;

    /// GameObject should never be copied
    GameObject(GameObject const&) = delete;
    GameObject& operator=(GameObject const&) = delete;

    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    void create()
    {
        try {
            auto const g = getGame();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::logic_error {
                "Gameobject cannot be created without gameinstace being set."
            };
        }
        doCreate();
    }

    void update(float const elapsed)
    {
        m_age += elapsed;
        doUpdate(elapsed);
    };
    void draw() const { doDraw(); };
    float getAge() const { return m_age; }
    void setAge(float t) { m_age = t; }

    void setGameInstance(std::weak_ptr<GameBase> g) { m_game = g; }
    std::shared_ptr<GameBase> getGame()
    {
        if (m_game.expired())
            throw std::exception(/*"ERROR: Cannot GameObject::getGame():  m_game expired!"*/);
        return m_game.lock();
    }
    // const version of getGame (required for draw functionality)
    std::shared_ptr<GameBase> getGame() const
    {
        if (m_game.expired())
            throw std::exception(/*"ERROR: Cannot GameObject::getGame():  m_game expired!"*/);
        return m_game.lock();
    }

    // kill this game Object (killed/dead game objects will get thrown out of any GameState
    void kill() { m_alive = false; }
    bool isAlive() const { return m_alive; }

protected:
    float m_age { 0.0f };

private:
    bool m_alive { true }; // is used to sort out "dead" game objects;

    std::weak_ptr<GameBase> m_game;

    virtual void doUpdate(float const /*elapsed*/) {};
    virtual void doDraw() const {};
    virtual void doCreate() {};
};

} // namespace jt
#endif
