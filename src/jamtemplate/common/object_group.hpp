#ifndef GUARD_JAMTEMPLATE_OBJECTGROUP_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_OBJECTGROUP_HPP_INCLUDEGUARD

#include "game_object.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace jt {

/// templated Object group for the purpose of holding specific Objects in a separate list.
/// Can be used as a GameObject.
/// For stored objects to be updated and drawn, you need to also add the object to the State itself
///
/// naming convention will differ here from the rest of the project as this is about to mimic the
/// std::vector interface
template <typename T>
class ObjectGroup : public GameObject {
public:
    using Sptr = std::shared_ptr<ObjectGroup<T>>;

    ObjectGroup() = default;
    auto begin() { return m_data.begin(); }
    auto end() { return m_data.end(); }
    auto cbegin() const { return m_data.cbegin(); }
    auto cend() const { return m_data.cend(); }

    auto size() const { return m_data.size(); }
    auto at(std::size_t idx) { return m_data.at(idx); }
    void push_back(std::weak_ptr<T> wptr) { m_data.push_back(wptr); }
    void emplace_back(std::weak_ptr<T>&& wptr) { m_data.emplace_back(std::move(wptr)); }

private:
    std::vector<std::weak_ptr<T>> m_data {};

    void doUpdate(const float /*elapsed*/) override
    {
        m_data.erase(std::remove_if(m_data.begin(), m_data.end(),
                         [](std::weak_ptr<T> wptr) { return wptr.expired(); }),
            m_data.end());
    }
};

template <typename T>
auto begin(ObjectGroup<T>& obj)
{
    return obj.begin();
}

template <typename T>
auto end(ObjectGroup<T>& obj)
{
    return obj.end();
}

} // namespace jt
#endif
