#include "tilemap/tileson_loader.hpp"
#include <backend_setup.hpp>
#include <pathfinder/node.hpp>
#include <shape.hpp>
#include <tilemap/tile_node.hpp>
#include <gtest/gtest.h>

TEST(TileNodeTest, GetCorrectDrawableNullptr)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr };
    ASSERT_EQ(tileNode.getDrawable(), nullptr);
}

TEST(TileNodeTest, GetCorrectDrawableoNullptr)
{
    auto shape = std::make_shared<jt::Shape>();
    shape->makeRect(jt::Vector2f { 20.0f, 20.0f }, getTextureManager());

    jt::tilemap::TileNode tileNode { shape, nullptr };
    ASSERT_EQ(tileNode.getDrawable(), shape);
}

TEST(TileNodeTest, GetCorrectNodeNullptr)
{
    jt::tilemap::TileNode tileNode { nullptr, nullptr };
    ASSERT_EQ(tileNode.getNode(), nullptr);
}

TEST(TileNodeTest, GetCorrectNodeNoNullptr)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    jt::tilemap::TileNode tileNode { nullptr, node };
    ASSERT_EQ(tileNode.getNode(), node);
}

TEST(TileNodeTest, GetBlockedFromNodeTrue)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    node->setBlocked(true);
    jt::tilemap::TileNode tileNode { nullptr, node };
    ASSERT_EQ(tileNode.getBlocked(), true);
}

TEST(TileNodeTest, GetBlockedFalse)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    node->setBlocked(false);
    jt::tilemap::TileNode tileNode { nullptr, node };
    ASSERT_EQ(tileNode.getBlocked(), false);
}

TEST(TileNodeTest, GetBlockedAfterSetBlockedTrue)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    jt::tilemap::TileNode tileNode { nullptr, node };
    tileNode.setBlocked(true);
    ASSERT_EQ(tileNode.getBlocked(), true);
}

TEST(TileNodeTest, GetBlockedAfterSetBlockedFalse)
{
    auto node = std::make_shared<jt::pathfinder::Node>();
    node->setBlocked(true);
    jt::tilemap::TileNode tileNode { nullptr, node };
    tileNode.setBlocked(false);
    ASSERT_EQ(tileNode.getBlocked(), false);
}
