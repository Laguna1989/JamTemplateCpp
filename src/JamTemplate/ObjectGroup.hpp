#ifndef JAMTEMPLATE_OBJECTGROUP_HPP_INCLUDEGUARD
#define JAMTEMPLATE_OBJECTGROUP_HPP_INCLUDEGUARD

#include <memory>
#include <vector>

#include "GameObject.hpp"
namespace JamTemplate {

/// templated Object group for the purpose of holding specific Objects in a separate list.
/// Can be used as a GameObject.
/// For stored objects to be updated and drawn, you need to also add the object to the State itself
///
/// naming convention will differ here from the rest of the project as this is about to mimic the std::vector interface
template <typename T>
class ObjectGroup : public GameObject {
public:
    using Sptr = std::shared_ptr<ObjectGroup<T>>;

    ObjectGroup() = default;

    auto begin() { return m_objects.begin(); }
    auto end() { return m_objects.end(); }

    auto at(size_t idx) { return m_objects.at(idx); }

    void push_back(std::weak_ptr<T> wptr)
    {
        m_objects.push_back(wptr);
    }

    void emplace_back(std::weak_ptr<T>&& wptr)
    {
        m_objects.emplace_back(wptr);
    }

    size_t size() { return m_objects.size(); }

private:
    std::vector<std::weak_ptr<T>> m_objects;

    void doUpdate(const float /*elapsed*/) override
    {
        m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
                            [](std::weak_ptr<T> wptr) {
                                return wptr.expired();
                            }),
            m_objects.end());
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

}
#endif
