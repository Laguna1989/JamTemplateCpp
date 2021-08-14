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

    EXPECT_EQ(wrapper.wrap(param), param);
}
TEST_P(IndexWrapperNoWrapTestFixture, OddSizeNoWrap)
{
    auto param = GetParam();
    IndexWrapper<17> wrapper;

    EXPECT_EQ(wrapper.wrap(param), param);
}

INSTANTIATE_TEST_SUITE_P(IndexWrapperTest, IndexWrapperNoWrapTestFixture,
    ::testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 15));

class IndexWrapperWrapTestFixture : public ::testing::TestWithParam<std::size_t> {
};

TEST_P(IndexWrapperWrapTestFixture, EvenSizeWrap)
{
    auto param = GetParam();
    IndexWrapper<16> wrapper;

    EXPECT_EQ(wrapper.wrap(wrapper.getSize() + param), param % wrapper.getSize());
}

TEST_P(IndexWrapperWrapTestFixture, OddSizeWrap)
{
    auto param = GetParam();
    IndexWrapper<15> wrapper;

    EXPECT_EQ(wrapper.wrap(wrapper.getSize() + param), param % wrapper.getSize());
}

INSTANTIATE_TEST_SUITE_P(IndexWrapperTest, IndexWrapperWrapTestFixture,
    ::testing::Values(1, 2, 3, 100, 200, 300, 1024, 2048));

TEST(CircularBufferSize2, ReadAndWrite)
{
    jt::CircularBuffer<int, 2> buffer;

    auto const value = 15;
    buffer[0] = value;
    EXPECT_EQ(buffer[0], value);

    auto const value2 = 1024;
    buffer[1] = value2;
    EXPECT_EQ(buffer[1], value2);
}

TEST(CircularBufferSize2, ReadAndWriteWithWrapAround)
{
    jt::CircularBuffer<int, 2> buffer;
    auto const value = 111;
    buffer[2] = value;
    EXPECT_EQ(buffer[2], value);
    EXPECT_EQ(buffer[0], value);

    auto const value2 = 15;
    buffer[3] = value2;
    EXPECT_EQ(buffer[3], value2);
    EXPECT_EQ(buffer[1], value2);
}

TEST(CircularBufferSize2, Push)
{
    jt::CircularBuffer<float, 2> buffer;
    auto const value = 1.123f;
    buffer.push(value);
    EXPECT_FLOAT_EQ(buffer[0], value);
}

TEST(CircularBufferSize2, EmptyBufferDoesNotContainElements)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    EXPECT_FALSE(buffer.contains(value1));
    EXPECT_FALSE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferContainsValuesAfterPush)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    buffer.push(value1);
    buffer.push(value2);
    EXPECT_TRUE(buffer.contains(value1));
    EXPECT_TRUE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferDoesNotContainValueAfterItIsPushedOutOfTheBuffer)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4U;
    auto const value2 = 8U;

    buffer.push(value1);
    buffer.push(value2);

    buffer.push(value2);
    EXPECT_FALSE(buffer.contains(value1));
    EXPECT_TRUE(buffer.contains(value2));
}
