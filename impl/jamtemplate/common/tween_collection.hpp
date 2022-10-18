#ifndef JAMTEMPLATE_TWEEN_COLLECTION_HPP
#define JAMTEMPLATE_TWEEN_COLLECTION_HPP

#include <tweens/tween_interface.hpp>
#include <memory>
#include <vector>

namespace jt {
class TweenCollection {
public:
    void clear();
    void add(std::shared_ptr<jt::TweenInterface> tween);
    void update(float tween);

    std::size_t size() const;

private:
    /// all tweens running in this collection
    std::vector<std::shared_ptr<jt::TweenInterface>> m_tweens {};

    /// This second vector is used as a level of indirection, because tweens might be added or
    /// removed while iterating over the vector. This would invalidat iterators, which
    /// leads to crashes.
    ///
    /// The idea is to not modify original vector directly when a Tween is added,
    /// but to place them in this vector first and add them to the original vector,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<TweenInterface>> m_tweensToAdd {};
};

} // namespace jt
#endif // JAMTEMPLATE_TWEEN_COLLECTION_HPP
