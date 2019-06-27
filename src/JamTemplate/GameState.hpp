#ifndef JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include "TweenBase.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

namespace JamTemplate {

// forward declaration
class Game;

class GameState : public GameObject {

public:
    using Sptr = std::shared_ptr<GameState>;
    GameState() = default;

    virtual ~GameState()
    {
        m_tweens.clear();
        m_tweensToAdd.clear();

        m_objectsToAdd.clear();
        m_objects.clear();
    };

    void create()
    {

        m_tweens.clear();
        m_tweensToAdd.clear();
        doCreate();
        initialize();
    };

    void add(GameObject::Sptr go)
    {
        go->setGameInstance(getGame());
        go->create();
        m_objectsToAdd.push_back(go);
    }
    void add(TweenBase::Sptr tb)
    {
        m_tweensToAdd.push_back(tb);
    }

    size_t getNumberOfObjects() const { return m_objects.size(); }

    bool hasBeenInitialized() const { return m_hasBeenInitialized; }

protected:
    void updateObjects(float elapsed)
    {
        cleanUpObjects();
        addNewObjects();

        for (auto& go : m_objects) {
            go->update(elapsed);
        }
    }

    void updateTweens(float elapsed)
    {
        if (!m_hasBeenInitialized)
            return;
        if (getAge() < 0.001f)
            return;
        while (true) {
            if (m_tweensToAdd.size() == 0)
                break;
            m_tweens.emplace_back(m_tweensToAdd.back());
            m_tweensToAdd.pop_back();
        }
        if (m_tweens.empty())
            return;
        m_tweens.erase(std::remove_if(m_tweens.begin(), m_tweens.end(), [](TweenBase::Sptr go) { return !(go->isAlive()); }), m_tweens.end());
        for (auto& tw : m_tweens) {
            tw->update(elapsed);
        }
    }

    void drawObjects() const
    {
        for (auto& go : m_objects) {
            go->draw();
        }
    }

    void internalUpdate(float elapsed)
    {
        doInternalUpdate(elapsed);
    }

    void internalDraw() const
    {
        doInternalDraw();
    }

private:
    /// all objects in the scene
    std::vector<GameObject::Sptr> m_objects;

    /// this is used as a level of indirection,
    /// because objects might add or remove m_objects while iterating over the m_objects vector,
    /// which invalidates pointers, which leads to crashes
    ///
    /// the idea is to not modify m_objects directly when a GameObject is added,
    /// but to place them in this vector first and add them to m_objects,
    /// once it is safe to do so.
    std::vector<GameObject::Sptr> m_objectsToAdd;

    /// all tweens running in this state
    std::vector<TweenBase::Sptr> m_tweens;
    std::vector<TweenBase::Sptr> m_tweensToAdd;

    bool m_hasBeenInitialized { false };
    void initialize() { m_hasBeenInitialized = true; }

    /// do not override this function in derived states, but override doInternalUpdate
    virtual void doUpdate(float const elapsed) override
    {
        updateObjects(elapsed);
        internalUpdate(elapsed);
        updateTweens(elapsed);
    }

    virtual void doInternalUpdate(float /*elapsed*/)
    {
    }

    void addNewObjects()
    {
        while (!m_objectsToAdd.empty()) {
            m_objects.emplace_back(std::move(m_objectsToAdd.back()));
            m_objectsToAdd.pop_back();
        }
    }
    void cleanUpObjects()
    {
        m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [](GameObject::Sptr go) { return !(go->isAlive()); }), m_objects.end());
    }

    virtual void doDraw() const override
    {
        internalDraw();
    };

    virtual void doInternalDraw() const
    {
        drawObjects();
    }

    virtual void doCreate() {};
};

}
#endif
