#include "tilemap/tile_layer.hpp"
#include <gtest/gtest.h>

using jt::tilemap::TileLayer;

class TilemapTileLayerTest : public ::testing::Test {
public:
    jt::tilemap::TileLayer tm;
    TilemapTileLayerTest()
        : tm { "assets/tileson_test.json", "ground" } {};
};

TEST_F(TilemapTileLayerTest, CanLoadJson)
{
    ASSERT_EQ(tm.getMapSizeInTiles().x(), 50);
    ASSERT_EQ(tm.getMapSizeInTiles().y(), 50);
}

TEST_F(TilemapTileLayerTest, DefaultPosition)
{
    ASSERT_FLOAT_EQ(tm.getPosition().x(), 0.0f);
    ASSERT_FLOAT_EQ(tm.getPosition().y(), 0.0f);
}

TEST_F(TilemapTileLayerTest, UpdateAndDraw)
{
    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST_F(TilemapTileLayerTest, ParseInvalidFile)
{
    auto func = []() { TileLayer tl { "assets/non_existing.json", "blarb" }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

TEST_F(TilemapTileLayerTest, DrawWithScreensizeHint)
{
    tm.setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST_F(TilemapTileLayerTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    jt::Vector2 const expected { 1.0f, 1.0f };
    ASSERT_EQ(tm.getScale(), expected);
}

TEST_F(TilemapTileLayerTest, GetGetOriginReturnsDefaultConstructedVector)
{
    ASSERT_EQ(tm.getOrigin(), jt::Vector2 {});
}

TEST_F(TilemapTileLayerTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tm.getGlobalBounds(), jt::Rect {});
}

TEST_F(TilemapTileLayerTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tm.getLocalBounds(), jt::Rect {});
}
