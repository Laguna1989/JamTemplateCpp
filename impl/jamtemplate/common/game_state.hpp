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
    virtual ~GameState();

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
    std::size_t getNumberOfObjects() const;

    /// Check if the State has been initialized
    /// \return true if inizialized, false otherwise
    bool hasBeenInitialized() const;

    /// Set auto update of Objects
    /// note: if the user sets autoupdate to false,
    /// he has to take care to do the respective calls himself
    /// \param performAutoUpdate
    void setAutoUpdateObjects(bool performAutoUpdate);

    /// Get auto update of Objects
    /// \return
    bool getAutoUpdateObjects() const;

    /// Set auto update of Tweens
    /// note: if the user sets autoupdate to false,
    /// he has to take care to do the respective calls himself
    /// \param performAutoUpdate
    void setAutoUpdateTweens(bool performAutoUpdate);

    /// Get auto updates of tweens
    /// \return
    bool getAutoUpdateTweens() const;

    /// Set auto draw of Objects
    /// \param performAudoDraw
    void setAutoDraw(bool performAudoDraw);

    /// Get auto draw of Objects
    /// \return
    bool getAutoDraw() const;

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

    /// do not override the do* function in derived states, but override doInternal* functions
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;
    virtual void doCreate() override;

    void internalCreate();
    void internalUpdate(float elapsed);
    void internalDraw() const;

    virtual void doInternalCreate() = 0;
    virtual void doInternalUpdate(float elapsed) = 0;
    virtual void doInternalDraw() const = 0;
};

} // namespace jt
#endif
