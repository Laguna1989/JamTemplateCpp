#include "circular_buffer.hpp"
#include <cstddef>
#include <gtest/gtest.h>
template <std::size_t size>
using IndexWrapper = jt::detail::IndexWrapper<size>;

class IndexWrapperNoWrapTestFixture : public ::testing::TestWithParam<std::size_t> {
};

TEST_P(IndexWrapperNoWrapTestFixture, EvenSizeNoWrap)
{
    auto param = GetParam();
    IndexWrapper<16> wrapper;

    ASSERT_EQ(wrapper.wrap(param), param);
}
TEST_P(IndexWrapperNoWrapTestFixture, OddSizeNoWrap)
{
    auto param = GetParam();
    IndexWrapper<17> wrapper;

    ASSERT_EQ(wrapper.wrap(param), param);
}

INSTANTIATE_TEST_SUITE_P(IndexWrapperTest, IndexWrapperNoWrapTestFixture,
    ::testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 15));

class IndexWrapperWrapTestFixture : public ::testing::TestWithParam<std::size_t> {
};

TEST_P(IndexWrapperWrapTestFixture, EvenSizeWrap)
{
    auto param = GetParam();
    IndexWrapper<16> wrapper;

    ASSERT_EQ(wrapper.wrap(wrapper.getSize() + param), param % wrapper.getSize());
}

TEST_P(IndexWrapperWrapTestFixture, OddSizeWrap)
{
    auto param = GetParam();
    IndexWrapper<15> wrapper;

    ASSERT_EQ(wrapper.wrap(wrapper.getSize() + param), param % wrapper.getSize());
}

INSTANTIATE_TEST_SUITE_P(IndexWrapperTest, IndexWrapperWrapTestFixture,
    ::testing::Values(1, 2, 3, 100, 200, 300, 1024, 2048));

TEST(CircularBufferSize2, ReadAndWrite)
{
    jt::CircularBuffer<int, 2> buffer;

    auto const value = 15;
    buffer[0] = value;
    ASSERT_EQ(buffer[0], value);

    auto const value2 = 1024;
    buffer[1] = value2;
    ASSERT_EQ(buffer[1], value2);
}

TEST(CircularBufferSize2, ReadAndWriteWithWrapAround)
{
    jt::CircularBuffer<int, 2> buffer;
    auto const value = 111;
    buffer[2] = value;
    ASSERT_EQ(buffer[2], value);
    ASSERT_EQ(buffer[0], value);

    auto const value2 = 15;
    buffer[3] = value2;
    ASSERT_EQ(buffer[3], value2);
    ASSERT_EQ(buffer[1], value2);
}

TEST(CircularBufferSize2, Push)
{
    jt::CircularBuffer<float, 2> buffer;
    auto const value = 1.123f;
    buffer.push(value);
    ASSERT_FLOAT_EQ(buffer[0], value);
}

TEST(CircularBufferSize2, EmptyBufferDoesNotContainElements)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    ASSERT_FALSE(buffer.contains(value1));
    ASSERT_FALSE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferContainsValuesAfterPush)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    buffer.push(value1);
    buffer.push(value2);
    ASSERT_TRUE(buffer.contains(value1));
    ASSERT_TRUE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferDoesNotContainValueAfterItIsPushedOutOfTheBuffer)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    buffer.push(value1);
    buffer.push(value2);

    buffer.push(value2);
    ASSERT_FALSE(buffer.contains(value1));
    ASSERT_TRUE(buffer.contains(value2));
}

jt::CircularBuffer<unsigned int, 2> createBufferWithValues(unsigned int a, unsigned int b)
{
    jt::CircularBuffer<unsigned int, 2> buffer;

    buffer.push(a);
    buffer.push(b);
    return buffer;
}

TEST(CircularBufferIterators, ValueAtBegin)
{
    auto const value1 = 4U;
    auto const value2 = 8U;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(value1, *buffer.begin());
}

TEST(CircularBufferSize, size)
{
    auto const value1 = 4U;
    auto const value2 = 8U;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(2, buffer.size());
}

TEST(CircularBufferIterators, ValueAtEnd)
{
    auto const value1 = 4U;
    auto const value2 = 8U;
    auto buffer = createBufferWithValues(value1, value2);
    auto last = buffer.end();
    --last;
    ASSERT_EQ(value2, *(last));
}

TEST(CircularBufferIterators, ValueAtCBegin)
{
    auto const value1 = 9U;
    auto const value2 = 3U;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(value1, *buffer.cbegin());
}

TEST(CircularBufferIterators, ValueAtCEnd)
{
    auto const value1 = 9U;
    auto const value2 = 3U;
    auto buffer = createBufferWithValues(value1, value2);
    auto clast = buffer.cend();
    --clast;
    ASSERT_EQ(value2, *(clast));
}

TEST(CircularBufferPushIndexTest, InitialValue)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    ASSERT_EQ(buffer.getPushIndex(), 0U);
}

TEST(CircularBufferPushIndexTest, ValueAfterPush)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.push(1u);
    ASSERT_EQ(buffer.getPushIndex(), 1U);
}

TEST(CircularBufferPushIndexTest, ValueAfterTwoPushes)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.push(1u);
    buffer.push(2u);
    ASSERT_EQ(buffer.getPushIndex(), 2U);
}

TEST(CircularBufferPushIndexTest, ValueAfterThreePushes)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.push(1u);
    buffer.push(2u);
    buffer.push(3u);
    ASSERT_EQ(buffer.getPushIndex(), 3U);
}
