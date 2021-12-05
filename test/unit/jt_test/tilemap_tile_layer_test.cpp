#include "tilemap/tile_layer.hpp"
#include <gtest/gtest.h>
#include "texture_manager_impl.hpp"

using jt::tilemap::TileLayer;

class TilemapTileLayerTest : public ::testing::Test {
public:
    std::shared_ptr<jt::tilemap::TileLayer> tileLayer;
    std::shared_ptr<jt::TextureManagerInterface> textureManager;

    void SetUp() override
    {
        textureManager = std::make_shared<jt::TextureManagerImpl>();
        tileLayer = std::make_shared<jt::tilemap::TileLayer>("assets/tileson_test.json", "ground", textureManager);
    }
};

TEST_F(TilemapTileLayerTest, CanLoadJson)
{
    ASSERT_EQ(tileLayer->getMapSizeInTiles().x(), 50);
    ASSERT_EQ(tileLayer->getMapSizeInTiles().y(), 50);
}

TEST_F(TilemapTileLayerTest, DefaultPosition)
{
    ASSERT_FLOAT_EQ(tileLayer->getPosition().x(), 0.0f);
    ASSERT_FLOAT_EQ(tileLayer->getPosition().y(), 0.0f);
}

TEST_F(TilemapTileLayerTest, UpdateAndDraw)
{
    tileLayer->update(0.1f);
    tileLayer->draw(nullptr);
}

TEST_F(TilemapTileLayerTest, ParseInvalidFile)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    auto func = [tm]() { TileLayer tl { "assets/non_existing.json", "blarb", tm }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

TEST_F(TilemapTileLayerTest, DrawWithScreensizeHint)
{
    tileLayer->setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    tileLayer->update(0.1f);
    tileLayer->draw(nullptr);
}

TEST_F(TilemapTileLayerTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    jt::Vector2 const expected { 1.0f, 1.0f };
    ASSERT_EQ(tileLayer->getScale(), expected);
}

TEST_F(TilemapTileLayerTest, GetGetOriginReturnsDefaultConstructedVector)
{
    ASSERT_EQ(tileLayer->getOrigin(), jt::Vector2 {});
}

TEST_F(TilemapTileLayerTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tileLayer->getGlobalBounds(), jt::Rect {});
}

TEST_F(TilemapTileLayerTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tileLayer->getLocalBounds(), jt::Rect {});
}
