#include "splitstring.hpp"
#include <gtest/gtest.h>
#include <string>

using jt::SplitString;

TEST(SplitStringTest, TestValidSplit)
{
    std::string const input { "test#1#2#whatever" };
    SplitString ss { input };
    auto const ssv = ss.split('#');
    EXPECT_EQ(ssv.size(), 4);
    EXPECT_EQ(ssv.at(0), "test");
    EXPECT_EQ(ssv.at(1), "1");
    EXPECT_EQ(ssv.at(2), "2");
    EXPECT_EQ(ssv.at(3), "whatever");
}

TEST(SplitStringTest, TestValidTwoSplit)
{
    std::string const input { "test#_abc_#bla" };
    SplitString ss { input };
    auto const ssv1 = ss.split('#');
    auto const ssv2 = ss.split('_');
    EXPECT_EQ(ssv2.size(), 3);
    EXPECT_EQ(ssv2.at(0), "test#");
    EXPECT_EQ(ssv2.at(1), "abc");
    EXPECT_EQ(ssv2.at(2), "#bla");
}
