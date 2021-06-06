#ifndef GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_SYSTEMHELPER_HPP_INCLUDEGUARD

#include "Vector.hpp"
#include <assert.h>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

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

} // namespace SystemHelper
} // namespace jt

#endif
