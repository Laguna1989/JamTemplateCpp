#include "mocks/mock_drawable.hpp"
#include "pathfinder/node.hpp"
#include "sdl_setup.hpp"
#include "shape.hpp"
#include "tilemap/tile_node.hpp"
#include <gtest/gtest.h>

TEST(TileNodeTest, GetCorrectDrawableNullptr)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr, false };
    ASSERT_EQ(tileNode.getDrawable(), nullptr);
}

TEST(TileNodeTest, GetCorrectDrawableoNullptr)
{
    auto shape = std::make_shared<jt::Shape>();
    shape->makeRect(jt::Vector2f { 20.0f, 20.0f }, getTextureManager());

    jt::tilemap::TileNode tileNode { shape, nullptr, false };
    ASSERT_EQ(tileNode.getDrawable(), shape);
}

TEST(TileNodeTest, GetCorrectNodeNullptr)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr, false };
    ASSERT_EQ(tileNode.getNode(), nullptr);
}

TEST(TileNodeTest, GetCorrectNodeNoNullptr)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    jt::tilemap::TileNode tileNode { nullptr, node, false };
    ASSERT_EQ(tileNode.getNode(), node);
}

TEST(TileNodeTest, GetBlockedTrue)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr, true };
    ASSERT_EQ(tileNode.getBlocked(), true);
}

TEST(TileNodeTest, GetBlockedFalse)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr, false };
    ASSERT_EQ(tileNode.getBlocked(), false);
}

TEST(TileNodeTest, GetBlockedAfterSetBlocked)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr, false };
    tileNode.setBlocked(true);
    ASSERT_EQ(tileNode.getBlocked(), true);
}
