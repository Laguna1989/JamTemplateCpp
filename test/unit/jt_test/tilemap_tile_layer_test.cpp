#include "sdl_setup.hpp"
#include "texture_manager_impl.hpp"
#include "tilemap/tile_layer.hpp"
#include "tilemap/tilemap_manager_tileson_impl.hpp"
#include "tilemap/tileson_loader.hpp"
#include <gtest/gtest.h>

using jt::tilemap::TileLayer;

class TilemapTileLayerTest : public ::testing::Test {
public:
    std::shared_ptr<jt::tilemap::TileLayer> tileLayer;
    jt::TextureManagerInterface& textureManager { getTextureManager() };

    void SetUp() override
    {
        jt::tilemap::TilesonLoader loader("assets/tileson_test.json");
        tileLayer = std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer("ground", textureManager));
    }
};

TEST_F(TilemapTileLayerTest, DefaultPosition)
{
    ASSERT_FLOAT_EQ(tileLayer->getPosition().x, 0.0f);
    ASSERT_FLOAT_EQ(tileLayer->getPosition().y, 0.0f);
}

TEST_F(TilemapTileLayerTest, UpdateAndDraw)
{
    tileLayer->update(0.1f);
    tileLayer->draw(nullptr);
}

TEST_F(TilemapTileLayerTest, DrawWithScreensizeHint)
{
    tileLayer->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });
    tileLayer->update(0.1f);
    tileLayer->draw(nullptr);
}

TEST_F(TilemapTileLayerTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    jt::Vector2f const expected { 1.0f, 1.0f };
    ASSERT_EQ(tileLayer->getScale(), expected);
}

TEST_F(TilemapTileLayerTest, GetGetOriginReturnsDefaultConstructedVector)
{
    ASSERT_EQ(tileLayer->getOrigin(), jt::Vector2f {});
}

TEST_F(TilemapTileLayerTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tileLayer->getGlobalBounds(), jt::Rectf {});
}

TEST_F(TilemapTileLayerTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    ASSERT_EQ(tileLayer->getLocalBounds(), jt::Rectf {});
}

TEST(TilemapLoaderTileson, ParseInvalidFile)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    auto func = [tilemapManager]() { tilemapManager->getMap("invalidFile.__123"); };
    ASSERT_THROW(func(), std::invalid_argument);
}
