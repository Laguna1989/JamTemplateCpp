#ifndef GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD

#include <iterator>
#include <memory>
#include <random>

namespace jt {
namespace SystemHelper {

/// Check if this is an uninitialized weak pointer
/// \tparam T value type of the weak pointer
/// \param weak the weack pointer to check
/// \return true if uninitialized, false otherwise
template <typename T>
bool is_uninitialized_weak_ptr(std::weak_ptr<T> const& weak)
{
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt {}) && !wt {}.owner_before(weak);
}

/// Erase helper for container access
/// \tparam ContainerT The container type
/// \tparam PredicateT The check function e.g. bool(T const&)
/// \param items the container
/// \param predicate the check function. If it returns true for an object, it will be removed
template <typename ContainerT, typename PredicateT>
void erase_if(ContainerT& items, const PredicateT& predicate)
{
    for (auto it = items.begin(); it != items.end();) {
        if (predicate(*it))
            it = items.erase(it);
        else
            ++it;
    }
}

/// Select random entry from container
/// \tparam Iter the iterator type
/// \tparam RandomGenerator the random generator
/// \param start begin iterator
/// \param end end iterator
/// \param g random generator
/// \return
template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g)
{
    std::uniform_int_distribution<std::size_t> dis(
        0U, static_cast<std::size_t>(std::distance(start, end)) - 1U);
    std::advance(start, dis(g));
    return start;
}

/// Select random entry between start and end
/// \tparam Iter
/// \param start
/// \param end
/// \return
template <typename Iter>
Iter select_randomly(Iter start, Iter end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

} // namespace SystemHelper
} // namespace jt
#endif
