#include <log/info_screen.hpp>
#include <mocks/mock_game.hpp>
#include <mocks/mock_input.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

TEST(InfoScreenTest, UpdateDoesNotThrow)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input {};
    EXPECT_CALL(*game.get(), input).WillRepeatedly(::testing::ReturnRef(input));

    jt::InfoScreen screen {};
    screen.setGameInstance(game);

    ASSERT_NO_THROW(screen.update(0.1f));
}

TEST(InfoScreenTest, DrawDoesNotThrow)
{
    auto game = std::make_shared<MockGame>();
    ::testing::NiceMock<MockInput> input {};
    EXPECT_CALL(*game.get(), input).WillRepeatedly(::testing::ReturnRef(input));

    jt::InfoScreen screen {};
    screen.setGameInstance(game);

    ASSERT_NO_THROW(screen.update(0.1f));
    ASSERT_NO_THROW(screen.draw());
}
