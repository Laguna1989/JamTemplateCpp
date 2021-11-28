#include "tilemap/tilelayer.hpp"
#include <gtest/gtest.h>

using jt::tilemap::TileLayer;

TEST(TilemapTest, CanLoadJson)
{
    TileLayer tm { "assets/tileson_test.json" };

    ASSERT_EQ(tm.getMapSizeInTiles().x(), 50);
    ASSERT_EQ(tm.getMapSizeInTiles().y(), 50);
}

TEST(TilemapTest, DefaultPosition)
{
    TileLayer tm { "assets/tileson_test.json" };

    ASSERT_FLOAT_EQ(tm.getPosition().x(), 0.0f);
    ASSERT_FLOAT_EQ(tm.getPosition().y(), 0.0f);
}

TEST(TilemapTest, UpdateAndDraw)
{
    TileLayer tm { "assets/tileson_test.json" };

    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, ParseInvalidFile)
{
    ASSERT_THROW(TileLayer tm { "assets/non_existing.json" }, std::logic_error);
}

TEST(TilemapTest, DrawWithScreensizeHint)
{
    TileLayer tm { "assets/tileson_test.json" };
    tm.setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    TileLayer tm { "assets/tileson_test.json" };
    jt::Vector2 const expected { 1.0f, 1.0f };
    ASSERT_EQ(tm.getScale(), expected);
}

TEST(TilemapTest, GetGetOriginReturnsDefaultConstructedVector)
{
    TileLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getOrigin(), jt::Vector2 {});
}

TEST(TilemapTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    TileLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getGlobalBounds(), jt::Rect {});
}

TEST(TilemapTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    TileLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getLocalBounds(), jt::Rect {});
}

// TODO move to objectLayerTest
// TEST(TilemapTest, JsonDoesContainObjectGroups)
//{
//    TileLayer tm { "assets/tileson_test.json" };
//
//    ASSERT_FALSE(tm.getObjectGroups().empty());
//}
// TEST(TilemapObjectGroupsTest, CountIsZeroForNonExistingLayer)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().count("abcd"), 0);
// }
//
// TEST(TilemapObjectGroupsTest, CountIsOneForExistingObjectLayer)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().count("objects"), 1);
// }
//
// TEST(TilemapObjectGroupsTest, AmountOfObjectsInObjectGroupIsCorrect)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").size(), 1U);
// }
//
// TEST(TilemapObjectGroupsTest, ObjectTypeIsParsedCorrectly)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).type, "type1");
// }
//
// TEST(TilemapObjectGroupsTest, ObjectNameIsParsedCorrectly)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).name, "object1");
// }
//
// TEST(TilemapObjectGroupsTest, ObjectPositionIsParsedCorrectly)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.x(), 256);
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.y(), 128);
// }
//
// TEST(TilemapObjectGroupsTest, ObjectSizeIsParsedCorrectly)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.x(), 64);
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.y(), 96);
// }
//
// TEST(TilemapObjectGroupsTest, ObjectRotationIsParsedCorrectly)
//{
//     TileLayer tm { "assets/tileson_test.json" };
//     ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).rotation, 45);
// }
