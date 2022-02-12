#ifndef GUARD_JAMTEMPLATE_COUNTED_OBJECT_HPP
#define GUARD_JAMTEMPLATE_COUNTED_OBJECT_HPP

#include <cstddef>
namespace jt {
template <class Obj>
class CountedObj {
public:
    CountedObj()
    {
        ++m_aliveObjects;
        ++m_createdObjects;
    }

    ~CountedObj() { --m_aliveObjects; }

    static size_t aliveObjects() { return m_aliveObjects; }
    static size_t createdObjects() { return m_createdObjects; }

private:
    static size_t m_aliveObjects;
    static size_t m_createdObjects;
};

template <typename T>
std::size_t CountedObj<T>::m_aliveObjects { 0 };

template <typename T>
std::size_t CountedObj<T>::m_createdObjects { 0 };

} // namespace jt

#endif // GUARD_JAMTEMPLATE_COUNTED_OBJECT_HPP
