#ifndef JAMTEMPLATE_SYSTEMHELPER_HPP
#define JAMTEMPLATE_SYSTEMHELPER_HPP

#include <algorithm>
#include <iterator>
#include <memory>
#include <random>
#include <stdexcept>
#include <unordered_set>

namespace jt {
namespace SystemHelper {

/// Check if this is an uninitialized weak pointer
/// \tparam T value type of the weak pointer
/// \param weak the weack pointer to check
/// \return true if uninitialized, false otherwise
template <typename T>
bool is_uninitialized_weak_ptr(std::weak_ptr<T> const& weak) noexcept
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
[[deprecated("use std::erase_if instead")]] void erase_if(
    ContainerT& items, PredicateT const& predicate)
{
    for (auto it = items.begin(); it != items.end();) {
        if (predicate(*it))
            it = items.erase(it);
        else
            ++it;
    }
}

/// Helper Function to remove all items of b from a.
/// \tparam ContainerT The container type
/// \param a the container from which elements should be removed
/// \param b the elements that should be removed.
template <typename ContainerT>
void remove_intersection(ContainerT& a, ContainerT const& b)
{
    std::unordered_set<typename ContainerT::value_type> const uniqueAs { a.cbegin(), a.cend() };
    std::unordered_multiset<typename ContainerT::value_type> st { uniqueAs.cbegin(),
        uniqueAs.cend() };

    st.insert(b.begin(), b.end());
    auto const predicate
        = [&st](typename ContainerT::value_type const& k) { return st.count(k) > 1; };
    std::erase_if(a, predicate);
}

/// Helper function to remove duplicates for containers of elements that can not be ordered
/// \tparam ForwardIterator Iterator type
/// \param first where to start
/// \param last where to end
/// \return first element to be removed
template <typename ForwardIterator>
ForwardIterator remove_duplicates(ForwardIterator first, ForwardIterator last)
{
    auto new_last = first;

    for (auto current = first; current != last; ++current) {
        if (std::find(first, new_last, *current) == new_last) {
            if (new_last != current)
                *new_last = *current;
            ++new_last;
        }
    }

    return new_last;
}

/// convert a vector of shared pointers to a vector of weak pointers.
/// \tparam T The type of objects being pointed to
/// \param pointers the vector of shared pointers
/// \return the vector of weak pointers
template <typename T>
std::vector<std::weak_ptr<T>> to_weak_pointers(std::vector<std::shared_ptr<T>> const& pointers)
{
    std::vector<std::weak_ptr<T>> weakPointers {};
    weakPointers.resize(pointers.size());
    for (auto i = 0u; i != pointers.size(); ++i) {
        weakPointers[i] = pointers[i];
    }
    return weakPointers;
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
    if (start == end) {
        throw std::invalid_argument { "cannot pick randomly from empty container" };
    }
    std::uniform_int_distribution<std::size_t> dis(
        0u, static_cast<std::size_t>(std::distance(start, end)) - 1u);
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

/// Select randomly from container
/// \tparam ContainerT Container type
/// \param container the container to pick from
/// \return one random element
template <typename ContainerT>
typename ContainerT::value_type select_randomly(ContainerT const& container)
{
    if (container.empty()) [[unlikely]] {
        throw std::invalid_argument { "cannot pick randomly from empty container" };
    }
    return *select_randomly(std::cbegin(container), std::cend(container));
}

bool checkForValidFile(std::string const& filename);

} // namespace SystemHelper
} // namespace jt
#endif
