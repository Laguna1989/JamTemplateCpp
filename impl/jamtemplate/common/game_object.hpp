#ifndef GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD

#include <memory>
#include <string>
#include <vector>

namespace jt {
// forward declaration
class GameInterface;

class GameObject {
public:
    using Sptr = std::shared_ptr<GameObject>;

    /// Destructor
    virtual ~GameObject() = default;

    /// Create the GameObject
    ///
    /// Will call doCreate
    void create();

    /// Update the GameObject
    ///
    /// Will call doUpdate()
    ///
    /// \param elapsed the elapsed time in seconds
    void update(float const elapsed);

    /// Draw the GameObject
    ///
    /// Will call doDraw
    void draw() const;

    /// Get the age of the GameObject
    /// \return the age in seconds
    float getAge() const;

    /// Set the age of the GameObject
    /// \param newAgeInSeconds the new age in seconds
    void setAge(float newAgeInSeconds);

    /// Set the game instance
    /// \param gameInstance the game instance
    void setGameInstance(std::weak_ptr<GameInterface> gameInstance);

    /// Get the game instance (non const)
    /// \return the game instance
    std::shared_ptr<GameInterface> getGame();

    /// Get the game instance (const)
    /// \return the game instance
    std::shared_ptr<GameInterface> getGame() const;

    /// Kill this GameObject
    ///
    /// kill will trigger the removal of the GameObject from the GameState
    void kill();

    /// Check if the GameObject is alive
    /// \return true if alive, false otherwise
    bool isAlive() const;

    /// Destroy the GameObject
    ///
    /// destroy will be called when the GameState removes the object
    /// NOTE: Do not modify or touch game here.
    void destroy();

    void storeActionCommand(std::shared_ptr<void> commandCallback);

    virtual std::string getName() const;

protected:
    float m_age { 0.0f };

private:
    bool m_alive { true }; // is used to sort out "dead" game objects;

    std::weak_ptr<GameInterface> m_game;

    std::vector<std::shared_ptr<void>> m_storedActionCommands;

    virtual void doCreate();
    virtual void doUpdate(float const /*elapsed*/);
    virtual void doDraw() const;

    virtual void doKill();

    // Do NOT modify the game or the gamestate in this function
    virtual void doDestroy();
};

} // namespace jt
#endif
