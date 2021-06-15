#include "Tilemap.hpp"
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
