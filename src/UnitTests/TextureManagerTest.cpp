#include "../JamTemplate/TextureManager.hpp"
#include "gtest/gtest.h"
#include <exception>

using JamTemplate::TextureManager;

class TextureManagerTest : public ::testing::Test {
public:
    void SetUp() override { TextureManager::reset(); }
};
TEST_F(TextureManagerTest, ValidFileCanBeLoaded)
{
    EXPECT_NO_THROW(TextureManager::get("assets/coin.png"));
}

TEST_F(TextureManagerTest, InvalidFileNameThrowsException)
{
    EXPECT_THROW(
        TextureManager::get("test12345_not_existing_file.txt.bla.invalid"), std::invalid_argument);
}

TEST_F(TextureManagerTest, GetTextureFromEmptyString)
{
    EXPECT_THROW(TextureManager::get(""), std::invalid_argument);
}

TEST_F(TextureManagerTest, InvalidSpecialOperation)
{
    EXPECT_THROW(TextureManager::get("#q#1#2#3"), std::invalid_argument);
}

TEST_F(TextureManagerTest, GetButton) { EXPECT_NO_THROW(TextureManager::get("#b#100#200")); }

TEST_F(TextureManagerTest, GetButtonInvalid)
{
    EXPECT_ANY_THROW(TextureManager::get("#b#10#20#30"));
    EXPECT_ANY_THROW(TextureManager::get("#b#-100#30"));
    EXPECT_ANY_THROW(TextureManager::get("#b#12asv12#30"));
    EXPECT_ANY_THROW(TextureManager::get("#b#0x12#30"));
}

TEST_F(TextureManagerTest, ColorReplaceWithoutLookup)
{
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0"), std::invalid_argument);
}

TEST_F(TextureManagerTest, ColorReplaceWithInvalidArgument)
{
    auto p = std::make_pair(sf::Color { 0, 0, 0 }, sf::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0#12"), std::invalid_argument);
}

TEST_F(TextureManagerTest, ColorReplaceWithInvalidNumber)
{
    auto p = std::make_pair(sf::Color { 0, 0, 0 }, sf::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0xFF"), std::invalid_argument);
}

TEST_F(TextureManagerTest, ColorReplaceValid)
{
    // position of a pixel with a certain color
    auto const xpos = 0U;
    auto const ypos = 8U;

    // sanity check that the correct image is present
    auto old = TextureManager::get("assets/coin.png").copyToImage().getPixel(xpos, ypos);
    auto const r = old.r;
    auto const g = old.g;
    auto const b = old.b;
    ASSERT_EQ(r, 0);
    ASSERT_EQ(g, 0);
    ASSERT_EQ(b, 0);
    ASSERT_EQ(old.a, 255);

    // actual check that corlor replacement is working.
    auto p = std::make_pair(sf::Color { r, g, b }, sf::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    auto const& t = TextureManager::get("#r#assets/coin.png#0");
    auto c = t.copyToImage().getPixel(xpos, ypos);

    EXPECT_EQ(c.r, 255);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 255);
    EXPECT_EQ(c.a, 255);
}
