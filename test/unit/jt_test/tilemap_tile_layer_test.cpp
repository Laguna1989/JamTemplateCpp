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
    std::shared_ptr<jt::TextureManagerInterface> textureManager;
    std::shared_ptr<jt::TilemapManagerInterface> tilemapManager;

    void SetUp() override
    {
        textureManager = getTextureManager();

        tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
        jt::tilemap::TilesonLoader loader(tilemapManager, "assets/tileson_test.json");
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

// TODO write a test for tileson loader
// TEST_F(TilemapTileLayerTest, ParseInvalidFile)
//{
//    auto tm = getTextureManager();
//    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
//
//    auto func = [tm, tilemapManager]() {
//        TileLayer tl { "assets/non_existing.json", tilemapManager, "blarb", tm };
//    };
//    ASSERT_THROW(func(), std::invalid_argument);
//}

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
