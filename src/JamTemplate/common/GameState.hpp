#ifndef GUARD_JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include <memory>
#include <vector>

namespace jt {

// forward declarations
class TweenBase;

class GameState : public GameObject {
public:
    using Sptr = std::shared_ptr<GameState>;
    GameState();

    virtual ~GameState();

    void add(GameObject::Sptr go);
    void add(std::shared_ptr<TweenBase> tb);

    std::size_t getNumberOfObjects() const;

    bool hasBeenInitialized() const;

protected:
    void updateObjects(float elapsed);
    void updateTweens(float elapsed);

    void drawObjects() const;

    // note: if the user sets autoupdate/autodraw to false,
    // he has to take care to do the respective calls himself
    void setAutoUpdateObjects(bool performAutoUpdate);
    void setAutoUpdateTweens(bool performAutoUpdate);
    void setAutoDraw(bool performAudoDraw);

private:
    /// all objects in the state
    std::vector<GameObject::Sptr> m_objects;

    /// this is used as a level of indirection,
    /// because objects might add or remove m_objects while iterating over the m_objects vector,
    /// which invalidates iterators, which leads to crashes.
    ///
    /// The idea is to not modify m_objects directly when a GameObject is added,
    /// but to place them in this vector first and add them to m_objects,
    /// once it is safe to do so.
    std::vector<GameObject::Sptr> m_objectsToAdd;

    /// all tweens running in this state
    std::vector<std::shared_ptr<TweenBase>> m_tweens;

    /// this is used as a level of indirection,
    /// because tweens might add or remove m_tweens while iterating over the m_tweens vector,
    /// which invalidates iterators, which leads to crashes.
    ///
    /// The idea is to not modify m_tweens directly when a Tween is added,
    /// but to place them in this vector first and add them to m_tweens,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<TweenBase>> m_tweensToAdd;

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
