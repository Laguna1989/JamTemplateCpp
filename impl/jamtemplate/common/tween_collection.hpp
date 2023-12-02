#ifndef JAMTEMPLATE_TWEEN_COLLECTION_HPP
#define JAMTEMPLATE_TWEEN_COLLECTION_HPP

#include <tweens/tween_interface.hpp>
#include <memory>
#include <vector>

namespace jt {

/// Manages a collection of tweens. Tweens that are no longer alive will automatically be removed.
class TweenCollection {
public:
    /// Add a tween to the collection
    /// \param tween shared pointer to the tween to be added
    void add(std::shared_ptr<jt::TweenInterface> tween);

    /// clear all tweens
    void clear() noexcept;

    ///  update all tweens in the collecion. This will also remove all tweens that are no
    /// longer alive
    /// \param elapsed elapsed time in seconds
    void update(float const elapsed);

    /// size of the collecion
    /// \return number of tweens in the collection
    std::size_t size() const noexcept;

private:
    /// all tweens running in this collection
    std::vector<std::shared_ptr<jt::TweenInterface>> m_tweens {};

    /// This second vector is used as a level of indirection, because tweens might be added or
    /// removed while iterating over the vector. This would invalidat iterators, which
    /// leads to all sorts of issues.
    ///
    /// The idea is to not modify original vector directly when a Tween is added,
    /// but to place them in this vector first and add them to the original vector,
    /// once it is safe to do so.
    std::vector<std::shared_ptr<TweenInterface>> m_tweensToAdd {};
};

} // namespace jt
#endif // JAMTEMPLATE_TWEEN_COLLECTION_HPP
