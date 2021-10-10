#include "color.hpp"
#include "texture_manager.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using jt::TextureManager;

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

TEST_F(TextureManagerTest, GetBlankInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(TextureManager::get("#f#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(TextureManager::get("#f#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#f#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(TextureManager::get("#f#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(TextureManager::get("#f#0x12#30"));
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
