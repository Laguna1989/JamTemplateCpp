#ifndef JAMTEMPLATE_CIRCULAR_BUFFER_HPP
#define JAMTEMPLATE_CIRCULAR_BUFFER_HPP

#include <math_helper.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <type_traits>

namespace jt {

namespace detail {

// primary template
template <std::size_t size, typename = void>
class IndexWrapper { };

// Wraparound would normally be done via modulo (a % size), but this is slow. If the size of the
// IndexWrapper is a power of two, wrapping can be expressed as a & (size -1).
template <std::size_t size>
class IndexWrapper<size, typename std::enable_if<jt::MathHelper::isPowerOfTwo(size)>::type> {
public:
    static_assert(size != 0, "Error: Cannot create IndexWrapper with capacity 0");

    std::size_t wrap(std::size_t const index) const noexcept { return index & m_mask; }

    std::size_t getSize() const noexcept { return size; }

private:
    size_t m_mask { size - 1 };
};

/*
 * Size     1000            8
 * Mask     0111            7
 * index1   0010 => 0010    2
 * index2   1010 => 0010    10 => 2
 *
 */

template <std::size_t size>
class IndexWrapper<size, typename std::enable_if<!jt::MathHelper::isPowerOfTwo(size)>::type> {
public:
    static_assert(size != 0, "Error: Cannot create IndexWrapper with capacity 0");

    std::size_t wrap(std::size_t const index) const noexcept { return index % size; }

    std::size_t getSize() const noexcept { return size; }
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
    T const& operator[](std::size_t const position) const
    {
        return m_data[m_wrapper.wrap(position)];
    }

    /// Access a value from the circular buffer
    /// \param position index
    /// \return reference to the element
    T& operator[](std::size_t const position) { return m_data[m_wrapper.wrap(position)]; }

    /// Check if the expected value is present in the circular buffer
    /// \param expected the value to be checked
    /// \return true if present, false otherwise
    bool contains(T const& expected)
    {
        return std::any_of(m_data.cbegin(), m_data.cend(),
            [&expected](auto const& value) { return value == expected; });
    }

    /// Begin iterator
    /// \return begin iterator
    IteratorT begin() noexcept { return m_data.begin(); }

    /// End iterator
    /// \return
    IteratorT end() noexcept { return m_data.end(); }

    /// Begin iterator
    /// \return begin iterator
    ConstIteratorT begin() const noexcept { return m_data.cbegin(); }

    /// End iterator
    /// \return
    ConstIteratorT end() const noexcept { return m_data.cend(); }

    /// Const begin iterator
    /// \return const begin iterator
    ConstIteratorT cbegin() const noexcept { return m_data.cbegin(); }

    /// Const end iterator
    /// \return const end iterator
    ConstIteratorT cend() const noexcept { return m_data.cend(); }

    /// Capacity of the circular buffer. Size of the underlying array.
    /// \return the total capacity
    std::size_t capacity() const noexcept { return m_data.size(); }

    /// Size of valid elements in the buffer
    /// \return the current size
    std::size_t size() const noexcept { return m_size; }

    /// Position of the head
    /// \return the head position
    std::size_t getHead() const noexcept { return m_wrapper.wrap(m_head); }

    /// Position of the tail
    /// \return the tail position
    std::size_t getTail() const noexcept { return m_wrapper.wrap(m_tail); }

    /// Put a new value into the circular buffer (possibly overwriting old values)
    /// \param value the new values
    void put(T const& value)
    {
        auto const indexToWrite = getTail();

        m_tail++;
        if (m_size == capacity()) {
            m_head++;
            // could implement latest/newest policy here if needed
        } else {
            m_size++;
        }

        m_data[indexToWrite] = value;
    }

    /// Get the value at the head position. If there is no value stored, a default constructed T
    /// will be returned.
    /// \return the value at the head position
    T get()
    {
        auto const indexToRead = getHead();

        m_head++;
        if (m_size == 0) {
            m_tail++;
            return T {};
        } else {
            m_size--;
        }
        return m_data[indexToRead];
    }

    auto data() const noexcept { return m_data.data(); }

private:
    detail::IndexWrapper<N> m_wrapper;
    ArrayT m_data {};

    std::size_t m_head { 0u };
    std::size_t m_tail { 0u };
    std::size_t m_size { 0u };
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
