#include "TextureManager.hpp"
#include "Color.hpp"
#include "gtest/gtest.h"
#include <exception>

using jt::TextureManager;
#ifndef ENABLE_WEB

class TextureManagerTest : public ::testing::Test {
public:
    void SetUp() override { TextureManager::reset(); }
};
TEST_F(TextureManagerTest, ValidFileCanBeLoaded)
{
    EXPECT_NO_THROW(TextureManager::get("assets/coin.png"));
}

TEST_F(TextureManagerTest, GetButton) { EXPECT_NO_THROW(TextureManager::get("#b#100#200")); }

TEST_F(TextureManagerTest, GetGlow)
{
    EXPECT_NO_THROW(TextureManager::get("#g#100#200"));
    EXPECT_NO_THROW(TextureManager::get("#g#100#255"));
    EXPECT_NO_THROW(TextureManager::get("#g#1#1"));
}

TEST_F(TextureManagerTest, GetVignette) { EXPECT_NO_THROW(TextureManager::get("#v#100#200")); }

TEST_F(TextureManagerTest, GetButtonInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(TextureManager::get("#b#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(TextureManager::get("#b#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#b#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#b#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(TextureManager::get("#b#0x12#30"));
}

TEST_F(TextureManagerTest, GetGlowInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(TextureManager::get("#g#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(TextureManager::get("#g#-100#30"));
    EXPECT_ANY_THROW(TextureManager::get("#g#0#30"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#g#100#3asdf0"));
    EXPECT_ANY_THROW(TextureManager::get("#g#100#-1"));
    EXPECT_ANY_THROW(TextureManager::get("#g#100#0"));
    EXPECT_ANY_THROW(TextureManager::get("#g#100#256"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#g#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(TextureManager::get("#g#0x12#30"));
}

TEST_F(TextureManagerTest, GetVignettteInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(TextureManager::get("#v#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(TextureManager::get("#v#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#v#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#v#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(TextureManager::get("#v#0x12#30"));
}

TEST_F(TextureManagerTest, ColorReplaceWithEmptyChangeSet)
{
    TextureManager::addSelectiveColorReplacement(0, {});
    EXPECT_NO_THROW(TextureManager::get("#r#assets/coin.png#0"));
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

TEST_F(TextureManagerTest, ColorReplaceWithoutLookup)
{
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0"), std::invalid_argument);
}

TEST_F(TextureManagerTest, ColorReplaceWithInvalidArgument)
{
    auto p = std::make_pair(jt::Color { 0, 0, 0 }, jt::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0#12"), std::invalid_argument);
}

TEST_F(TextureManagerTest, ColorReplaceWithInvalidNumber)
{
    auto p = std::make_pair(jt::Color { 0, 0, 0 }, jt::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#0xFF"), std::invalid_argument);
}
TEST_F(TextureManagerTest, ColorReplaceWithInvalidIndex)
{
    auto p = std::make_pair(jt::Color { 0, 0, 0 }, jt::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    EXPECT_THROW(TextureManager::get("#r#assets/coin.png#4"), std::invalid_argument);
}
#endif

// TODO test uses SFML specific functions
#if 0
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
    auto p = std::make_pair(jt::Color { r, g, b }, jt::Color { 255, 0, 255 });
    TextureManager::addSelectiveColorReplacement(0, { p });
    auto const& t = TextureManager::get("#r#assets/coin.png#0");
    auto c = t.copyToImage().getPixel(xpos, ypos);

    EXPECT_EQ(c.r, 255);
    EXPECT_EQ(c.g, 0);
    EXPECT_EQ(c.b, 255);
    EXPECT_EQ(c.a, 255);
}
#endif
