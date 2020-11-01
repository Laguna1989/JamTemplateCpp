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
/// naming convention will differ here from the rest of the project as this is about to mimic the
/// std::vector interface
template <typename T>
class ObjectGroup : public GameObject, public std::vector<std::weak_ptr<T>> {
public:
    using Sptr = std::shared_ptr<ObjectGroup<T>>;

    ObjectGroup() = default;

private:
    void doUpdate(const float /*elapsed*/) override
    {
        erase(std::remove_if(begin(), end(), [](std::weak_ptr<T> wptr) { return wptr.expired(); }),
            end());
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

} // namespace JamTemplate
#endif
