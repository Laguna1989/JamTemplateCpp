#include "game_object_collection.hpp"
#include <algorithm>

void jt::GameObjectCollection::clear()
{
    m_objects.clear();
    m_objectsToAdd.clear();
}

void jt::GameObjectCollection::add(std::shared_ptr<jt::GameObjectInterface> object)
{
    m_objectsToAdd.push_back(object);
}

void jt::GameObjectCollection::update(float elapsed)
{
    addNewObjects();
    cleanUpObjects();

    for (auto& go : m_objects) {
        go->update(elapsed);
    }
}

void jt::GameObjectCollection::draw() const
{
    for (auto const& go : m_objects) {
        go->draw();
    }
}

void jt::GameObjectCollection::cleanUpObjects()
{
    std::erase_if(m_objects, [](auto go) {
        bool const isDead = !go->isAlive();
        if (isDead) {
            go->destroy();
        }
        return isDead;
    });
}

void jt::GameObjectCollection::addNewObjects()
{
    while (!m_objectsToAdd.empty()) {
        m_objects.emplace_back(std::move(m_objectsToAdd.back()));
        m_objectsToAdd.pop_back();
    }
}

std::size_t jt::GameObjectCollection::size() const
{
    return m_objectsToAdd.size() + m_objects.size();
}
