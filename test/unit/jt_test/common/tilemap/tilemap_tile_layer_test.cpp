#include <backend_setup.hpp>
#include <texture_manager_impl.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tileson_loader.hpp>
#include <gtest/gtest.h>

using jt::tilemap::TileLayer;

namespace {
jt::TilemapCache cache;
}

class TilemapTileLayerTest : public ::testing::Test {
public:
    std::shared_ptr<jt::tilemap::TileLayer> tileLayer;
    jt::TextureManagerInterface& textureManager { getTextureManager() };

    void SetUp() override
    {
        jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test.json");
        tileLayer = std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer("ground", textureManager, "assets/test/unit/jt_test/"));
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
    tileLayer->draw(std::shared_ptr<jt::RenderTargetInterface> { nullptr });
}

TEST_F(TilemapTileLayerTest, DrawWithScreensizeHint)
{
    tileLayer->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });
    tileLayer->update(0.1f);
    tileLayer->draw(std::shared_ptr<jt::RenderTargetInterface> { nullptr });
}

TEST_F(TilemapTileLayerTest, UpdateAndDrawWithScreensizeHintWithColorFunction)
{
    tileLayer->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });
    tileLayer->setColorFunction([](auto const& p) {
        return jt::Color {
            255u,
            255u,
            255u,
            static_cast<std::uint8_t>((p.x / 20.0f + p.y / 20.0f) * 255u),
        };
    });
    tileLayer->update(0.1f);
    tileLayer->draw(getRenderTarget());
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
    jt::Rectf const expectedRect { 0.0f, 0.0f, 1600.0f, 1600.0f };
    ASSERT_EQ(tileLayer->getGlobalBounds(), expectedRect);
}

TEST_F(TilemapTileLayerTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    jt::Rectf const expectedRect { 0.0f, 0.0f, 1600.0f, 1600.0f };
    ASSERT_EQ(tileLayer->getLocalBounds(), expectedRect);
}

TEST(TilemapLoaderTileson, ParseInvalidFile)
{
    auto tilemapManager = std::make_shared<jt::TilemapCache>();
    auto func = [tilemapManager]() { tilemapManager->get("invalidFile.__123"); };
    ASSERT_THROW(func(), std::invalid_argument);
}
