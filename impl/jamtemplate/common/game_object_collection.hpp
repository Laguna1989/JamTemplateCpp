#ifndef JAMTEMPLATE_GAME_OBJECT_COLLECTION_HPP
#define JAMTEMPLATE_GAME_OBJECT_COLLECTION_HPP

#include <game_object.hpp>
#include <memory>
#include <vector>

namespace jt {
class GameObjectCollection {
public:
    void clear();
    void add(std::shared_ptr<jt::GameObject> object);
    void update(float elapsed);
    void draw() const;
    std::size_t size() const;

private:
    /// all objects in the state
    std::vector<std::shared_ptr<jt::GameObject>> m_objects {};

    /// this is used as a level of indirection,
    /// because objects might add or remove m_objects while iterating over the m_objects vector,
    /// which invalidates iterators, which leads to crashes.
    ///
    /// The idea is to not modify m_objects directly when a GameObject is added,
    /// but to place them in this vector first and add them to m_objects,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<jt::GameObject>> m_objectsToAdd {};
    void addNewObjects();
    void cleanUpObjects();
};

} // namespace jt

#endif // JAMTEMPLATE_GAME_OBJECT_COLLECTION_HPP
