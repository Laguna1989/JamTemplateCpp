#include <game_interface.hpp>
#include <game_state.hpp>
#include <log/console.hpp>
#include <log/info_screen.hpp>
#include <algorithm>

jt::GameState::~GameState()
{
    m_tweens.clear();
    m_tweensToAdd.clear();

    m_objectsToAdd.clear();
    m_objects.clear();
}

void jt::GameState::start() { m_started = true; }
bool jt::GameState::hasBeenInitialized() const { return m_started; }

void jt::GameState::add(std::shared_ptr<jt::GameObject> gameObject)
{
    gameObject->setGameInstance(getGame());
    gameObject->create();
    if (!m_objects.empty()) {
        m_objectsToAdd.push_back(gameObject);
    } else {
        m_objects.push_back(gameObject);
    }
}

void jt::GameState::add(std::shared_ptr<TweenInterface> obj) { m_tweensToAdd.push_back(obj); }

size_t jt::GameState::getNumberOfObjects() const { return m_objects.size(); }

void jt::GameState::doCreate() { internalCreate(); }
void jt::GameState::doUpdate(float const elapsed) { internalUpdate(elapsed); }
void jt::GameState::doDraw() const { internalDraw(); };

void jt::GameState::internalCreate()
{
    getGame()->logger().debug("create GameState: " + getName(), { "jt" });
    m_tweens.clear();
    m_tweensToAdd.clear();
    doInternalCreate();
    add(std::make_shared<jt::Console>(getGame()->logger()));
    add(std::make_shared<jt::InfoScreen>());
    start();
}

void jt::GameState::internalUpdate(float elapsed)
{
    if (m_doAutoUpdateObjects) {
        updateObjects(elapsed);
    }
    doInternalUpdate(elapsed);
    if (m_doAutoUpdateTweens) {
        updateTweens(elapsed);
    }
}

void jt::GameState::internalDraw() const
{
    if (m_doAutoDraw) {
        drawObjects();
    }
    doInternalDraw();
}

void jt::GameState::updateObjects(float elapsed)
{
    basicUpdateObjects(elapsed);

    for (auto& go : m_objects) {
        go->update(elapsed);
    }
}

void jt::GameState::basicUpdateObjects(float /*elapsed*/)
{
    cleanUpObjects();
    addNewObjects();
}

void jt::GameState::updateTweens(float elapsed)
{
    if (!m_started) {
        return;
    }
    auto const expected_minimum_age = 0.001f;
    if (getAge() < expected_minimum_age) {
        return;
    }
    m_tweens.insert(m_tweens.end(), m_tweensToAdd.cbegin(), m_tweensToAdd.cend());
    m_tweensToAdd.clear();
    if (m_tweens.empty()) {
        return;
    }
    m_tweens.erase(
        std::remove_if(m_tweens.begin(), m_tweens.end(),
            [](std::shared_ptr<TweenInterface> const& obj) { return !(obj->isAlive()); }),
        m_tweens.cend());

    for (auto& obj : m_tweens) {
        obj->update(elapsed);
    }
}

void jt::GameState::drawObjects() const
{
    for (const auto& go : m_objects) {
        go->draw();
    }
}

void jt::GameState::addNewObjects()
{
    while (!m_objectsToAdd.empty()) {
        m_objects.emplace_back(std::move(m_objectsToAdd.back()));
        m_objectsToAdd.pop_back();
    }
}
void jt::GameState::cleanUpObjects()
{
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
                        [](auto go) {
                            bool const isDead = !go->isAlive();
                            if (isDead) {
                                go->destroy();
                            }
                            return isDead;
                        }),
        m_objects.end());
}

void jt::GameState::setAutoUpdateObjects(bool performAutoUpdate)
{
    m_doAutoUpdateObjects = performAutoUpdate;
}
bool jt::GameState::getAutoUpdateObjects() const { return m_doAutoUpdateObjects; }

void jt::GameState::setAutoUpdateTweens(bool performAutoUpdate)
{
    m_doAutoUpdateTweens = performAutoUpdate;
}
bool jt::GameState::getAutoUpdateTweens() const { return m_doAutoUpdateTweens; }

void jt::GameState::setAutoDraw(bool performAudoDraw) { m_doAutoDraw = performAudoDraw; }
bool jt::GameState::getAutoDraw() const { return m_doAutoDraw; }
