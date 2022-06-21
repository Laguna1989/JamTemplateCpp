#ifndef JAMTEMPLATE_GAMESTATE_HPP
#define JAMTEMPLATE_GAMESTATE_HPP

#include <game_object.hpp>
#include <tweens/tween_interface.hpp>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class GameState : public jt::GameObject {
public:
    using Sptr = std::shared_ptr<jt::GameState>;

    virtual ~GameState();

    /// Add a GameObject to the GameState
    ///
    /// Added gameobjects will be updated and drawn by the GameState
    ///
    /// \param gameObject the GameObject
    void add(std::shared_ptr<jt::GameObject> gameObject);

    /// Add a GameObjectInterface to the GameState
    /// Added Objects will be updated and drawn by the GameState
    /// \param obj the GameObject
    void add(std::shared_ptr<TweenInterface> obj);

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
    void basicUpdateObjects(float elapsed);
    void updateTweens(float obj);

    void drawObjects() const;

private:
    /// all objects in the state
    std::vector<std::shared_ptr<GameObject>> m_objects {};

    /// this is used as a level of indirection,
    /// because objects might add or remove m_objects while iterating over the m_objects vector,
    /// which invalidates iterators, which leads to crashes.
    ///
    /// The idea is to not modify m_objects directly when a GameObject is added,
    /// but to place them in this vector first and add them to m_objects,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<GameObject>> m_objectsToAdd {};

    /// all tweens running in this state
    std::vector<std::shared_ptr<TweenInterface>> m_tweens {};

    /// this is used as a level of indirection, because GameObjects might add or remove objects
    /// while iterating over the objects vector, which invalidates iterators, which leads to
    /// crashes.
    ///
    /// The idea is to not modify m_gameObjects directly when a Tween is added,
    /// but to place them in this vector first and add them to m_gameObjects,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<TweenInterface>> m_tweensToAdd {};

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

    void addNewObjects();
    void cleanUpObjects();
};

} // namespace jt
#endif
