#include "sdl_setup.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using jt::TextureManagerImpl;

class TextureManagerTest : public ::testing::Test {
protected:
    jt::TextureManagerInterface& m_manager { getTextureManager() };
};

TEST_F(TextureManagerTest, ValidFileCanBeLoaded)
{
    EXPECT_NO_THROW(m_manager.get("assets/coin.png"));
}

TEST_F(TextureManagerTest, GetButton) { EXPECT_NO_THROW(m_manager.get("#b#100#200")); }

TEST_F(TextureManagerTest, GetGlow)
{
    EXPECT_NO_THROW(m_manager.get("#g#100#200"));
    EXPECT_NO_THROW(m_manager.get("#g#100#255"));
    EXPECT_NO_THROW(m_manager.get("#g#1#1"));
}

TEST_F(TextureManagerTest, GetVignette) { EXPECT_NO_THROW(m_manager.get("#v#100#200")); }

TEST_F(TextureManagerTest, GetButtonInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(m_manager.get("#b#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(m_manager.get("#b#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#b#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#b#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(m_manager.get("#b#0x12#30"));
}

TEST_F(TextureManagerTest, GetGlowInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(m_manager.get("#g#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(m_manager.get("#g#-100#30"));
    EXPECT_ANY_THROW(m_manager.get("#g#0#30"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#g#100#3asdf0"));
    EXPECT_ANY_THROW(m_manager.get("#g#100#-1"));
    EXPECT_ANY_THROW(m_manager.get("#g#100#0"));
    EXPECT_ANY_THROW(m_manager.get("#g#100#256"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#g#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(m_manager.get("#g#0x12#30"));
}

TEST_F(TextureManagerTest, GetVignettteInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(m_manager.get("#v#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(m_manager.get("#v#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#v#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#v#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(m_manager.get("#v#0x12#30"));
}

TEST_F(TextureManagerTest, GetBlankInvalid)
{
    // too many arguments
    EXPECT_ANY_THROW(m_manager.get("#f#10#20#30"));
    // negative value
    EXPECT_ANY_THROW(m_manager.get("#f#-100#30"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#f#100#3asdf0"));
    // chars in size argument
    EXPECT_ANY_THROW(m_manager.get("#f#12asv12#30"));
    // hex numbers not allowed
    EXPECT_ANY_THROW(m_manager.get("#f#0x12#30"));
}

TEST_F(TextureManagerTest, InvalidFileNameThrowsException)
{
    EXPECT_THROW(
        m_manager.get("test12345_not_existing_file.txt.bla.invalid"), std::invalid_argument);
}

TEST_F(TextureManagerTest, GetTextureFromEmptyString)
{
    EXPECT_THROW(m_manager.get(""), std::invalid_argument);
}

TEST_F(TextureManagerTest, InvalidSpecialOperation)
{
    EXPECT_THROW(m_manager.get("#q#1#2#3"), std::invalid_argument);
}

TEST_F(TextureManagerTest, GetNumberOfTexturesIsInitiallyZero)
{
    ASSERT_EQ(m_manager.getNumberOfTextures(), 0U);
}

TEST_F(TextureManagerTest, GetNumberOfTexturesIsTwoAfterGetTexture)
{
    EXPECT_NO_THROW(m_manager.get("assets/coin.png"));
    // two because of normal texture + flash texture
    ASSERT_EQ(m_manager.getNumberOfTextures(), 2U);
}

TEST_F(TextureManagerTest, GetNumberOfTexturesIsZeroAfterReset)
{
    EXPECT_NO_THROW(m_manager.get("assets/coin.png"));
    EXPECT_NO_THROW(m_manager.reset());
    ASSERT_EQ(m_manager.getNumberOfTextures(), 0U);
}
