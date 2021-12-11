#ifndef JAMTEMPLATE_CIRCULAR_BUFFER_HPP_GUARD
#define JAMTEMPLATE_CIRCULAR_BUFFER_HPP_GUARD

#include "math_helper.hpp"
#include <algorithm>
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

/*
 * Size     1000            8
 * Maske    0111            7
 * index1   0010 => 0010    2
 * index2   1010 => 0010    10 => 2
 *
 */

template <std::size_t size>
class IndexWrapper<size, typename std::enable_if<!jt::MathHelper::is_powerof2(size)>::type> {
public:
    static_assert(size != 0, "Error: Cannot create IndexWrapper with size 0");
    std::size_t wrap(const std::size_t index) const { return index % size; }
    std::size_t getSize() const { return size; }
};

} // namespace detail

template <typename T, std::size_t N>
class CircularBuffer {
public:
    using ArrayT = std::array<T, N>;
    using IteratorT = typename ArrayT::iterator;
    using ConstIteratorT = typename ArrayT::const_iterator;

    /// Access a const value from the circular buffer
    /// \param position index
    /// \return const reference to the element
    T const& operator[](std::size_t const position) const { return m_data[wrapper.wrap(position)]; }

    /// Access a value from the circular buffer
    /// \param position index
    /// \return reference to the element
    T& operator[](std::size_t const position) { return m_data[wrapper.wrap(position)]; }

    /// Check if the expected value is present in the circular buffer
    /// \param expected the value to be checked
    /// \return true if present, false otherwise
    bool contains(T const& expected)
    {
        return std::any_of(m_data.cbegin(), m_data.cend(),
            [&expected](auto const& value) { return value == expected; });
    }

    /// Push a new value into the circular buffer (possibly overwriting old values)
    /// \param value the new values
    void push(T const& value) { m_data[wrapper.wrap(m_pushIndex++)] = value; }

    /// Begin iterator
    /// \return begin iterator
    IteratorT begin() { return m_data.begin(); }

    /// End iterator
    /// \return
    IteratorT end() { return m_data.end(); }

    /// Const begin iterator
    /// \return const begin iterator
    ConstIteratorT cbegin() const { return m_data.cbegin(); }

    /// Const end iterator
    /// \return const end iterator
    ConstIteratorT cend() const { return m_data.cend(); }

    /// Size of the circular buffer
    /// \return the size
    std::size_t size() const { return m_data.size(); }

    std::size_t getPushIndex() const { return m_pushIndex; }

private:
    detail::IndexWrapper<N> wrapper;
    ArrayT m_data;
    std::size_t m_pushIndex { 0 };
};

template <typename T, std::size_t N>
auto begin(CircularBuffer<T, N>& obj)
{
    return obj.begin();
}

template <typename T, std::size_t N>
auto end(CircularBuffer<T, N>& obj)
{
    return obj.end();
}

template <typename T, std::size_t N>
auto cbegin(CircularBuffer<T, N> const& obj)
{
    return obj.cbegin();
}

template <typename T, std::size_t N>
auto cend(CircularBuffer<T, N> const& obj)
{
    return obj.cend();
}

} // namespace jt
#endif
