#include "game_state.hpp"
#include "game_interface.hpp"
#include "logging/console.hpp"
#include "logging/info_screen.hpp"
#include "tweens/tween_base.hpp"
#include <algorithm>

namespace jt {
GameState ::~GameState()
{
    m_tweens.clear();
    m_tweensToAdd.clear();

    m_objectsToAdd.clear();
    m_objects.clear();
}

void GameState::start() { m_started = true; }
bool GameState::hasBeenInitialized() const { return m_started; }

void GameState::add(GameObject::Sptr gameObject)
{
    gameObject->setGameInstance(getGame());
    gameObject->create();
    if (!m_objects.empty()) {
        m_objectsToAdd.push_back(gameObject);
    } else {
        m_objects.push_back(gameObject);
    }
}

void GameState::add(Tween::Sptr tb) { m_tweensToAdd.push_back(tb); }

size_t GameState::getNumberOfObjects() const { return m_objects.size(); }

void GameState::doCreate() { internalCreate(); }
void GameState::doUpdate(float const elapsed) { internalUpdate(elapsed); }
void GameState::doDraw() const { internalDraw(); };

void GameState::internalCreate()
{
    getGame()->getLogger().debug("create GameState: " + getName(), { "jt" });
    m_tweens.clear();
    m_tweensToAdd.clear();
    doInternalCreate();
    add(std::make_shared<jt::Console>(getGame()->getLogger()));
    add(std::make_shared<jt::InfoScreen>());
    start();
}

void GameState::internalUpdate(float elapsed)
{
    getGame()->gfx().window().updateGui(elapsed);

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
    getGame()->gfx().window().startRenderGui();
    if (m_doAutoDraw) {
        drawObjects();
    }
    doInternalDraw();
}

void GameState::updateObjects(float elapsed)
{
    basicUpdateObjects(elapsed);

    for (auto& go : m_objects) {
        go->update(elapsed);
    }
}

void GameState::basicUpdateObjects(float /*elapsed*/)
{
    cleanUpObjects();
    addNewObjects();
}

void GameState::updateTweens(float elapsed)
{
    if (!m_started) {
        return;
    }
    auto const expected_minimum_age = 0.001f;
    if (getAge() < expected_minimum_age) {
        return;
    }
    while (true) {
        if (m_tweensToAdd.empty()) {
            break;
        }
        m_tweens.emplace_back(m_tweensToAdd.back());
        m_tweensToAdd.pop_back();
    }
    if (m_tweens.empty()) {
        return;
    }
    m_tweens.erase(std::remove_if(m_tweens.begin(), m_tweens.end(),
                       [](Tween::Sptr tween) { return !(tween->isAlive()); }),
        m_tweens.end());
    for (auto& tw : m_tweens) {
        tw->update(elapsed);
    }
}

void GameState::drawObjects() const
{
    for (const auto& go : m_objects) {
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
                            bool const isDead = !go->isAlive();
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
bool GameState::getAutoUpdateObjects() const { return m_doAutoUpdateObjects; }

void GameState::setAutoUpdateTweens(bool performAutoUpdate)
{
    m_doAutoUpdateTweens = performAutoUpdate;
}
bool GameState::getAutoUpdateTweens() const { return m_doAutoUpdateTweens; }

void GameState::setAutoDraw(bool performAudoDraw) { m_doAutoDraw = performAudoDraw; }
bool GameState::getAutoDraw() const { return m_doAutoDraw; }

} // namespace jt
