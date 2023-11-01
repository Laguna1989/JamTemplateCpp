#include <line.hpp>
#include <texture_manager_impl.hpp>
#include <gtest/gtest.h>

TEST(LineTest, LineVectorIsZeroByDefault)
{
    auto const line = jt::Line {};
    jt::Vector2f const expectedResult { 0.0f, 0.0f };
    ASSERT_EQ(line.getLineVector(), expectedResult);
}

TEST(LineTest, LineVectorIsSetCorrectlyByConstructor)
{
    jt::Vector2f const expectedResult { 15.4f, -22.0f };
    auto const line = jt::Line { expectedResult };
    ASSERT_EQ(line.getLineVector(), expectedResult);
}

TEST(LineTest, SetLineVector)
{
    auto line = jt::Line {};
    jt::Vector2f const expectedResult { -20.0f, -40.0f };
    line.setLineVector(expectedResult);
    ASSERT_EQ(line.getLineVector(), expectedResult);
}
