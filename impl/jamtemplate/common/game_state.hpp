#ifndef JAMTEMPLATE_GAMESTATE_HPP
#define JAMTEMPLATE_GAMESTATE_HPP

#include <game_object.hpp>
#include <game_object_interface.hpp>
#include <tweens/tween_interface.hpp>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class GameObjectCollection;
class TweenCollection;

class GameState : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<jt::GameState>;

    GameState();

    /// Destructor
    ~GameState() override;

    /// Add a GameObject to the GameState
    ///
    /// Added gameobjects will be updated and drawn by the GameState
    ///
    /// \param gameObject the GameObject
    void add(std::shared_ptr<jt::GameObject> gameObject);

    /// Add a GameObjectInterface to the GameState
    /// Added Objects will be updated and drawn by the GameState
    /// \param tween the GameObject
    void add(std::shared_ptr<TweenInterface> tween);

    /// Get the number of GameObjects in the State
    /// \return the number of gameobjects
    std::size_t getNumberOfObjects() const noexcept;

    /// Enter the GameState
    void enter();

    /// Check if the State has been initialized
    /// \return true if initialized, false otherwise
    bool hasBeenInitialized() const noexcept;

    /// Set auto update of Objects
    /// note: if the user sets autoupdate to false,
    /// he has to take care to do the respective calls himself
    /// \param performAutoUpdate
    void setAutoUpdateObjects(bool performAutoUpdate) noexcept;

    /// Get auto update of Objects
    /// \return
    bool getAutoUpdateObjects() const noexcept;

    /// Set auto update of Tweens
    /// note: if the user sets autoupdate to false,
    /// he has to take care to do the respective calls himself
    /// \param performAutoUpdate
    void setAutoUpdateTweens(bool performAutoUpdate) noexcept;

    /// Get auto updates of tweens
    /// \return
    bool getAutoUpdateTweens() const noexcept;

    /// Set auto draw of Objects
    /// \param performAudoDraw
    void setAutoDraw(bool performAudoDraw) noexcept;

    /// Get auto draw of Objects
    /// \return
    bool getAutoDraw() const noexcept;

protected:
    void updateObjects(float elapsed);
    void updateTweens(float obj);

    void drawObjects() const;

private:
    std::unique_ptr<jt::TweenCollection> m_tweens;
    std::unique_ptr<jt::GameObjectCollection> m_objects;

    bool m_doAutoUpdateObjects { true };
    bool m_doAutoUpdateTweens { true };
    bool m_doAutoDraw { true };

    bool m_started { false };
    void start();

    /// do not override the do* function in derived states, but override on* functions
    virtual void doCreate() override;
    virtual void doEnter();
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void internalCreate();
    void internalEnter();
    void internalUpdate(float elapsed);
    void internalDraw() const;

    virtual void onCreate() = 0;
    virtual void onEnter() = 0;
    virtual void onUpdate(float elapsed) = 0;
    virtual void onDraw() const = 0;

    void checkForMuteUnmute();
};

} // namespace jt
#endif
