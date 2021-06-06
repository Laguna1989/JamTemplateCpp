#ifndef GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD

#include <memory>

namespace jt {
// forward declaration
class GameInterface;

class GameObject {
public:
    using Sptr = std::shared_ptr<GameObject>;

    GameObject() = default;

    virtual ~GameObject() = default;

    /// GameObjects should never be copied
    GameObject(GameObject const&) = delete;
    GameObject& operator=(GameObject const&) = delete;

    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    void create();

    void update(float const elapsed);

    void draw() const;
    float getAge() const;
    void setAge(float t);

    void setGameInstance(std::weak_ptr<GameInterface> g);
    std::shared_ptr<GameInterface> getGame();
    // const version of getGame (required for draw functionality)
    std::shared_ptr<GameInterface> getGame() const;

    // kill this game Object (killed/dead game objects will get thrown out of any GameState)
    void kill();
    bool isAlive() const;

    // will be called, just before object is thrown out of the gamestate.
    void destroy();

protected:
    float m_age { 0.0f };

private:
    bool m_alive { true }; // is used to sort out "dead" game objects;

    std::weak_ptr<GameInterface> m_game;

    virtual void doCreate();
    virtual void doUpdate(float const /*elapsed*/);
    virtual void doDraw() const;
    virtual void doKill();

    // Do NOT modify the game or the gamestate in this function
    virtual void doDestroy();
};

} // namespace jt
#endif
