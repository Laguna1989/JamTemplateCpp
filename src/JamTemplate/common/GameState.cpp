#include "GameState.hpp"
#include "GameInterface.hpp"
#include "TweenBase.hpp"
#include <algorithm>
#include <numeric>

namespace jt {

GameState::GameState() = default;

GameState ::~GameState()
{
    m_tweens.clear();
    m_tweensToAdd.clear();

    m_objectsToAdd.clear();
    m_objects.clear();
}

void GameState::start() { m_started = true; }
bool GameState::hasBeenInitialized() const { return m_started; }

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

void GameState::doCreate() { internalCreate(); }
void GameState::doUpdate(float const elapsed) { internalUpdate(elapsed); }
void GameState::doDraw() const { internalDraw(); };

void GameState::internalCreate()
{
    m_tweens.clear();
    m_tweensToAdd.clear();
    doInternalCreate();
    start();
}

void GameState::internalUpdate(float elapsed)
{
    if (m_doAutoUpdateObjects) {
        updateObjects(elapsed);
    }
    doInternalUpdate(elapsed);
    if (m_doAutoUpdateTweens) {
        updateTweens(elapsed);
    }
}

void GameState::internalDraw() const
{
    if (m_doAutoDraw) {
        drawObjects();
    }
    doInternalDraw();
}

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
    if (!m_started)
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
                        [](GameObject::Sptr go) {
                            bool isDead = !go->isAlive();
                            if (isDead) {
                                go->destroy();
                            }
                            return isDead;
                        }),
        m_objects.end());
}

void GameState::setAutoUpdateObjects(bool performAutoUpdate)
{
    m_doAutoUpdateObjects = performAutoUpdate;
}

void GameState::setAutoUpdateTweens(bool performAutoUpdate)
{
    m_doAutoUpdateTweens = performAutoUpdate;
}
void GameState::setAutoDraw(bool performAudoDraw) { m_doAutoDraw = performAudoDraw; }

} // namespace jt
