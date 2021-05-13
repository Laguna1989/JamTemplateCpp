#ifndef JAMTEMPLATE_CIRCULAR_BUFFER_HPP_GUARD
#define JAMTEMPLATE_CIRCULAR_BUFFER_HPP_GUARD

#include "MathHelper.hpp"
#include <array>
#include <cstddef>
#include <type_traits>

namespace jt {

namespace detail {

// primary template
template <std::size_t size, typename = void>
class IndexWrapper {
};

template <std::size_t size>
class IndexWrapper<size, typename std::enable_if<jt::MathHelper::is_powerof2(size)>::type> {
public:
    static_assert(size != 0, "Error: Cannot create IndexWrapper with size 0");
    std::size_t wrap(const std::size_t index) const { return index & m_mask; }
    std::size_t getSize() const { return size; }

private:
    size_t m_mask { size - 1 };
};

template <std::size_t size>
class IndexWrapper<size, typename std::enable_if<!jt::MathHelper::is_powerof2(size)>::type> {
public:
    static_assert(size != 0, "Error: Cannot create IndexWrapper with size 0");
    std::size_t wrap(const std::size_t index) const { return index % size; }
    std::size_t getSize() const { return size; }
};

} // namespace detail

template <typename T, std::size_t size>
class CircularBuffer {
public:
    T const& operator[](std::size_t const position) const { return m_data[wrapper.wrap(position)]; }
    T& operator[](std::size_t const position) { return m_data[wrapper.wrap(position)]; }

private:
    detail::IndexWrapper<size> wrapper;
    std::array<T, size> m_data;
};
} // namespace jt
#endif
