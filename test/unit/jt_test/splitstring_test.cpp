#include "strutils.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(SplitStringTest, TestValidSplit)
{
    std::string const input { "test#1#2#whatever" };
    auto const ssv = strutil::split(input, "#");
    EXPECT_EQ(ssv.size(), 4);
    EXPECT_EQ(ssv.at(0), "test");
    EXPECT_EQ(ssv.at(1), "1");
    EXPECT_EQ(ssv.at(2), "2");
    EXPECT_EQ(ssv.at(3), "whatever");
}

TEST(SplitStringTest, StartsWithSeparator)
{
    std::string const input { "#b#10#20#30" };
    auto const ssv = strutil::split(input, '#');
    ASSERT_EQ(ssv[0], "");
    ASSERT_EQ(ssv[1], "b");
    ASSERT_EQ(ssv[2], "10");
    ASSERT_EQ(ssv[3], "20");
    ASSERT_EQ(ssv[4], "30");
}

TEST(SplitStringTest, TestValidTwoSplit)
{
    std::string const input { "test#_abc_#bla" };
    auto const ssv = strutil::split(input, '_');
    EXPECT_EQ(ssv.size(), 3);
    EXPECT_EQ(ssv.at(0), "test#");
    EXPECT_EQ(ssv.at(1), "abc");
    EXPECT_EQ(ssv.at(2), "#bla");
}
