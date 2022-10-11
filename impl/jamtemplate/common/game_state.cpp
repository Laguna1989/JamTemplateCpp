#include <game_interface.hpp>
#include <game_object_collection.hpp>
#include <game_state.hpp>
#include <log/console.hpp>
#include <log/info_screen.hpp>
#include <tween_collection.hpp>
#include <algorithm>

jt::GameState::GameState()
{
    m_objects = std::make_unique<jt::GameObjectCollection>();
    m_tweens = std::make_unique<jt::TweenCollection>();
}

jt::GameState::~GameState()
{
    m_tweens->clear();
    m_objects->clear();
}

void jt::GameState::start() { m_started = true; }
bool jt::GameState::hasBeenInitialized() const { return m_started; }

void jt::GameState::add(std::shared_ptr<jt::GameObject> gameObject)
{
    gameObject->setGameInstance(getGame());
    gameObject->create();
    m_objects->add(gameObject);
}

void jt::GameState::add(std::shared_ptr<TweenInterface> tween) { m_tweens->add(tween); }

size_t jt::GameState::getNumberOfObjects() const { return m_objects->size(); }

void jt::GameState::doCreate() { internalCreate(); }
void jt::GameState::doUpdate(float const elapsed) { internalUpdate(elapsed); }
void jt::GameState::doDraw() const { internalDraw(); };

void jt::GameState::internalCreate()
{
    getGame()->logger().debug("create GameState: " + getName(), { "jt" });
    m_tweens->clear();
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

void jt::GameState::updateObjects(float elapsed) { m_objects->update(elapsed); }

void jt::GameState::updateTweens(float elapsed)
{
    if (!m_started) {
        return;
    }
    auto const expected_minimum_age = 0.001f;
    if (getAge() < expected_minimum_age) {
        return;
    }
    m_tweens->update(elapsed);
}

void jt::GameState::drawObjects() const { m_objects->draw(); }

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
