#include <circular_buffer.hpp>
#include <gtest/gtest.h>

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
    buffer.put(value);
    ASSERT_FLOAT_EQ(buffer[0], value);
}

TEST(CircularBufferSize2, EmptyBufferDoesNotContainElements)
{
    jt::CircularBuffer<unsigned int, 2> buffer {};
    auto const value1 = 4u;
    auto const value2 = 8u;

    ASSERT_FALSE(buffer.contains(value1));
    ASSERT_FALSE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferContainsValuesAfterPush)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4u;
    auto const value2 = 8u;

    buffer.put(value1);
    buffer.put(value2);
    ASSERT_TRUE(buffer.contains(value1));
    ASSERT_TRUE(buffer.contains(value2));
}

TEST(CircularBufferSize2, BufferDoesNotContainValueAfterItIsPushedOutOfTheBuffer)
{
    jt::CircularBuffer<unsigned int, 2> buffer;
    auto const value1 = 4u;
    auto const value2 = 8u;

    buffer.put(value1);
    buffer.put(value2);

    buffer.put(value2);
    ASSERT_FALSE(buffer.contains(value1));
    ASSERT_TRUE(buffer.contains(value2));
}

jt::CircularBuffer<unsigned int, 2> createBufferWithValues(unsigned int a, unsigned int b)
{
    jt::CircularBuffer<unsigned int, 2> buffer;

    buffer.put(a);
    buffer.put(b);
    return buffer;
}

TEST(CircularBufferIterators, ValueAtBegin)
{
    auto const value1 = 4u;
    auto const value2 = 8u;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(value1, *buffer.begin());
}

TEST(CircularBufferCapacity, Capacity)
{
    auto const value1 = 4u;
    auto const value2 = 8u;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(2, buffer.capacity());
}

TEST(CircularBufferIterators, ValueAtEnd)
{
    auto const value1 = 4u;
    auto const value2 = 8u;
    auto buffer = createBufferWithValues(value1, value2);
    auto last = buffer.end();
    --last;
    ASSERT_EQ(value2, *(last));
}

TEST(CircularBufferIterators, ValueAtCBegin)
{
    auto const value1 = 9u;
    auto const value2 = 3u;
    auto buffer = createBufferWithValues(value1, value2);

    ASSERT_EQ(value1, *buffer.cbegin());
}

TEST(CircularBufferIterators, ValueAtCEnd)
{
    auto const value1 = 9u;
    auto const value2 = 3u;
    auto buffer = createBufferWithValues(value1, value2);
    auto clast = buffer.cend();
    --clast;
    ASSERT_EQ(value2, *(clast));
}

TEST(CircularBufferTailTest, InitialValue)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    ASSERT_EQ(buffer.getTail(), 0u);
}

TEST(CircularBufferTailTest, ValueAfterPut)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    ASSERT_EQ(buffer.getTail(), 1u);
}

TEST(CircularBufferTailTest, ValueAfterTwoPuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    ASSERT_EQ(buffer.getTail(), 0u);
}

TEST(CircularBufferTailTest, ValueAfterThreePuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    buffer.put(3u);
    ASSERT_EQ(buffer.getTail(), 1u);
}

TEST(CircularBufferHeadTest, InitialValue)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    ASSERT_EQ(buffer.getHead(), 0u);
}

TEST(CircularBufferHeadTest, ValueAfterPut)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    ASSERT_EQ(buffer.getHead(), 0u);
}

TEST(CircularBufferHeadTest, ValueAfterTwoPuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    ASSERT_EQ(buffer.getHead(), 0u);
}

TEST(CircularBufferHeadTest, ValueAfterThreePuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    buffer.put(3u);
    ASSERT_EQ(buffer.getHead(), 1u);
}

TEST(CircularBufferGetTest, InitialGet)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};

    ASSERT_EQ(buffer.get(), 0u);
}

TEST(CircularBufferGetTest, GetAfterSinglePut)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    auto const expectedValue = 15u;
    buffer.put(expectedValue);

    ASSERT_EQ(buffer.get(), expectedValue);
}

TEST(CircularBufferGetTest, GetAfterTwoPuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    auto const expectedValue = 15u;
    buffer.put(expectedValue);
    buffer.put(1u);

    ASSERT_EQ(buffer.get(), expectedValue);
}

TEST(CircularBufferGetTest, GetAfterThreePuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    buffer.put(3u);

    ASSERT_EQ(buffer.get(), 2u);
    ASSERT_EQ(buffer.get(), 3u);
}

TEST(CircularBufferGetTest, GetAfterGet)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};

    buffer.put(15u);

    (void)buffer.get();

    ASSERT_EQ(buffer.get(), 0u);
}

TEST(CircularBufferGetTest, GetAfterTwoGets)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};

    buffer.put(11u);
    buffer.put(12u);

    (void)buffer.get();
    (void)buffer.get();

    ASSERT_EQ(buffer.get(), 0u);
}

TEST(CircularBufferGetTest, GetAfterPutAfterGet)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    // t,h
    // 0    0
    // size 0

    // get empty value
    (void)buffer.get();
    //      t, h
    // 0    0
    // size 0

    // put actual value
    buffer.put(11u);
    // t    h
    // 0    11
    // size 1

    // get actual value
    ASSERT_EQ(buffer.get(), 11u);
    // t,h
    // 0    11
    // size 0
}

TEST(CircularBufferGetTest, MultipleGetAfterPutAfterGet)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    // t,h
    // 0    0
    // size 0

    // get empty value
    (void)buffer.get();
    //      t, h
    // 0    0
    // size 0

    // put actual value
    buffer.put(11u);
    // t    h
    // 0    11
    // size 1

    // get actual value
    ASSERT_EQ(buffer.get(), 11u);
    // t,h
    // 0    11
    // size 0

    ASSERT_EQ(buffer.get(), 0u);
    //      t,h
    // 0    11
    // size 0

    // next get returns default initialized T
    ASSERT_EQ(buffer.get(), 0u);
}

TEST(CircularBufferSize, GetInitialValue)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    ASSERT_EQ(buffer.size(), 0);
}

TEST(CircularBufferSize, GetSizeAfterSinglePut)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    ASSERT_EQ(buffer.size(), 1);
}

TEST(CircularBufferSize, GetSizeAfterTwoPuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);
    ASSERT_EQ(buffer.size(), 2);
}

TEST(CircularBufferSize, GetSizeAfterThreePuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 2> {};
    buffer.put(1u);
    buffer.put(2u);

    buffer.put(3u);
    ASSERT_EQ(buffer.size(), 2);
}

TEST(CircularBufferSize, GetSizeAfterFourPuts)
{
    auto buffer = jt::CircularBuffer<unsigned int, 3> {};

    buffer.put(1u);
    buffer.put(2u);
    buffer.put(3u);

    buffer.put(4u);

    ASSERT_EQ(buffer.size(), 3);
}

TEST(CircularBufferTest, CanBeSorted)
{
    auto buffer = jt::CircularBuffer<unsigned int, 7> {};

    buffer.put(10u);
    buffer.put(9u);
    buffer.put(8u);
    buffer.put(1u);
    buffer.put(2u);
    buffer.put(3u);
    buffer.put(4u);

    std::sort(buffer.begin(), buffer.end());
    ASSERT_EQ(buffer[0], 1u);
    ASSERT_EQ(buffer[1], 2u);
    ASSERT_EQ(buffer[2], 3u);
    ASSERT_EQ(buffer[3], 4u);
    ASSERT_EQ(buffer[4], 8u);
    ASSERT_EQ(buffer[5], 9u);
    ASSERT_EQ(buffer[6], 10u);
}
