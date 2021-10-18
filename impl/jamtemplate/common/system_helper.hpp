#ifndef GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD

#include <memory>
#include  <random>
#include  <iterator>

namespace jt {
namespace SystemHelper {

template <typename T>
bool is_uninitialized_weak_ptr(std::weak_ptr<T> const& weak)
{
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt {}) && !wt {}.owner_before(weak);
}

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

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<std::size_t> dis(0U, static_cast<std::size_t>(std::distance(start, end)) - 1U);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


} // namespace SystemHelper
} // namespace jt
#endif
