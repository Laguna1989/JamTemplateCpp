#include <backend_setup.hpp>
#include <sprite.hpp>
#include <texture_manager_impl.hpp>
#include <gtest/gtest.h>

TEST(SpriteSFMLTest, LoadSpriteFromSfTexture)
{
    sf::Texture t;
    t.create(20u, 20u);
    jt::Sprite s;
    s.fromTexture(t);
    ASSERT_FLOAT_EQ(s.getLocalBounds().width, 20.0f);
    ASSERT_FLOAT_EQ(s.getLocalBounds().height, 20.0f);
}

TEST(SpriteSFMLTest, GetSfSprite)
{
    jt::Sprite s { "assets/test/unit/jt_test/coin.png", getTextureManager() };

    sf::Sprite value = s.getSFSprite();
    ASSERT_EQ(value.getLocalBounds().left, s.getLocalBounds().left);
    ASSERT_EQ(value.getLocalBounds().top, s.getLocalBounds().top);
    ASSERT_EQ(value.getLocalBounds().width, s.getLocalBounds().width);
    ASSERT_EQ(value.getLocalBounds().height, s.getLocalBounds().height);
}
