#include <backend_setup.hpp>
#include <texture_manager_impl.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tileson_loader.hpp>
#include <gtest/gtest.h>

namespace {
jt::TilemapCache cache;
}

TEST(TilesonLoaderTestNodes, LoadCorrectAmountOfNodes)
{
    jt::TextureManagerInterface& textureManager { getTextureManager() };
    jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test.json");
    auto const nodes = loader.loadTileNodesFromLayer("ground", textureManager);

    ASSERT_EQ(nodes.size(), 2500U);
    ASSERT_TRUE(nodes.at(0)->getBlocked());
}

TEST(TilesonLoaderTestNodes, LoadedNodesAreSortedYFirst)
{
    jt::TextureManagerInterface& textureManager { getTextureManager() };
    jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test.json");
    auto const nodes = loader.loadTileNodesFromLayer("ground", textureManager);

    for (auto i = 0U; i != nodes.size(); ++i) {
        auto const mapSizeX = 50;
        auto const expectedX = i / mapSizeX;
        auto const expectedY = i % mapSizeX;

        jt::Vector2u const expectedPosition { expectedX, expectedY };
        auto const node = nodes.at(i)->getNode();
        ASSERT_EQ(node->getTilePosition(), expectedPosition);
    }
}

TEST(TilesonLoaderTestCollisions, LoadsCorrectAmountOfCollisions)
{
    jt::TextureManagerInterface& textureManager { getTextureManager() };
    jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test.json");

    auto const collisions = loader.loadCollisionsFromLayer("ground");
    ASSERT_EQ(collisions.getRects().size(), 83U);
}

TEST(TilesonLoaderTestCollisions, LoadedCollidersAreSortedYFirst)
{
    jt::TextureManagerInterface& textureManager { getTextureManager() };
    jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test.json");

    auto const collisions = loader.loadCollisionsFromLayer("ground");
    ASSERT_EQ(collisions.getRects().at(0).left, 0U);
    ASSERT_EQ(collisions.getRects().at(0).top, 0U);
    ASSERT_EQ(collisions.getRects().at(1).left, 0U);
    ASSERT_EQ(collisions.getRects().at(1).top, 32U);
}

TEST(TilesonLoaderTest, MapSizeInTiles)
{
    jt::TextureManagerInterface& textureManager { getTextureManager() };
    jt::tilemap::TilesonLoader loader(cache, "assets/test/unit/jt_test/tileson_test_small.json");
    jt::Vector2u const expectedValue { 14U, 15U };
    ASSERT_EQ(loader.getMapSizeInTiles(), expectedValue);
}
