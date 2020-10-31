#include "GameState.hpp"
#include "TweenBase.hpp"
#include <algorithm>
#include <numeric>

namespace JamTemplate {

GameState::GameState() = default;

GameState ::~GameState()
{
    m_tweens.clear();
    m_tweensToAdd.clear();

    m_objectsToAdd.clear();
    m_objects.clear();
};

void GameState::create()
{
    m_tweens.clear();
    m_tweensToAdd.clear();
    doCreate();
    initialize();
};

void GameState::add(GameObject::Sptr go)
{
    go->setGameInstance(getGame());
    go->create();
    if (!m_objects.empty()) {
        m_objectsToAdd.push_back(go);
    } else {
        m_objects.push_back(go);
    }
}

void GameState::add(TweenBase::Sptr tb) { m_tweensToAdd.push_back(tb); }

size_t GameState::getNumberOfObjects() const { return m_objects.size(); }

bool GameState::hasBeenInitialized() const { return m_hasBeenInitialized; }

void GameState::updateObjects(float elapsed)
{
    cleanUpObjects();
    addNewObjects();

    for (auto& go : m_objects) {
        go->update(elapsed);
    }
}

void GameState::updateTweens(float elapsed)
{
    if (!m_hasBeenInitialized)
        return;
    if (getAge() < 0.001f)
        return;
    while (true) {
        if (m_tweensToAdd.empty())
            break;
        m_tweens.emplace_back(m_tweensToAdd.back());
        m_tweensToAdd.pop_back();
    }
    if (m_tweens.empty())
        return;
    m_tweens.erase(std::remove_if(m_tweens.begin(), m_tweens.end(),
                       [](TweenBase::Sptr go) { return !(go->isAlive()); }),
        m_tweens.end());
    for (auto& tw : m_tweens) {
        tw->update(elapsed);
    }
}

void GameState::drawObjects() const
{
    for (auto& go : m_objects) {
        go->draw();
    }
}

void GameState::internalUpdate(float elapsed) { doInternalUpdate(elapsed); }

void GameState::internalDraw() const { doInternalDraw(); }

void GameState::initialize() { m_hasBeenInitialized = true; }

/// do not override this function in derived states, but override doInternalUpdate
void GameState::doUpdate(float const elapsed)
{
    updateObjects(elapsed);
    internalUpdate(elapsed);
    updateTweens(elapsed);
}

void GameState::doInternalUpdate(float /*elapsed*/) { }

void GameState::addNewObjects()
{
    while (!m_objectsToAdd.empty()) {
        m_objects.emplace_back(std::move(m_objectsToAdd.back()));
        m_objectsToAdd.pop_back();
    }
}
void GameState::cleanUpObjects()
{
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
                        [](GameObject::Sptr go) { return !(go->isAlive()); }),
        m_objects.end());
}

void GameState::doDraw() const { internalDraw(); };

void GameState::doInternalDraw() const { drawObjects(); }

void GameState::doCreate() { doInternalCreate(); };

void GameState::doInternalCreate() {};
} // namespace JamTemplate
