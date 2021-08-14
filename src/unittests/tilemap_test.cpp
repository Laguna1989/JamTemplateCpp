#include "tilemap.hpp"
#include <gtest/gtest.h>

TEST(TilemapTest, CanLoadJson)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    ASSERT_EQ(tm.getMapSizeInTiles().x(), 50);
    ASSERT_EQ(tm.getMapSizeInTiles().y(), 50);
}

TEST(TilemapTest, DefaultPosition)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    ASSERT_FLOAT_EQ(tm.getPosition().x(), 0.0f);
    ASSERT_FLOAT_EQ(tm.getPosition().y(), 0.0f);
}

TEST(TilemapTest, JsonDoesNotContainObjectGroups)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    ASSERT_TRUE(tm.getObjectGroups().empty());
}

TEST(TilemapTest, UpdateAndDraw)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, ParseInvalidFile)
{
    ASSERT_THROW(jt::Tilemap tm { "assets/non_existing.json" }, std::logic_error);
}

TEST(TilemapTest, DrawWithScreensizeHint)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    tm.setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, GetColorWillReturnBlackByDefault)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getColor(), jt::colors::Black);
}

TEST(TilemapTest, GetColorWillAlwaysReturnBlack)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    tm.setColor(::jt::colors::Red);
    ASSERT_EQ(tm.getColor(), jt::colors::Black);
}

TEST(TilemapTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getScale(), jt::Vector2 {});
}

TEST(TilemapTest, GetGetOriginReturnsDefaultConstructedVector)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getOrigin(), jt::Vector2 {});
}

TEST(TilemapTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getGlobalBounds(), jt::Rect {});
}

TEST(TilemapTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getLocalBounds(), jt::Rect {});
}
