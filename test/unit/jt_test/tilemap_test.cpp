#include "tilemap.hpp"
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

TEST(TilemapTest, JsonDoesContainObjectGroups)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    ASSERT_FALSE(tm.getObjectGroups().empty());
}

TEST(TilemapTest, UpdateAndDraw)
{
    jt::Tilemap tm { "assets/tileson_test.json" };

    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, ParseInvalidFile)
{
    ASSERT_THROW(jt::Tilemap tm { "assets/non_existing.json" }, std::logic_error);
}

TEST(TilemapTest, DrawWithScreensizeHint)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    tm.setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
    tm.update(0.1f);
    tm.draw(nullptr);
}

TEST(TilemapTest, GetScaleAlwaysReturnsDefaultConstructedVector)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    jt::Vector2 const expected { 1.0f, 1.0f };
    ASSERT_EQ(tm.getScale(), expected);
}

TEST(TilemapTest, GetGetOriginReturnsDefaultConstructedVector)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getOrigin(), jt::Vector2 {});
}

TEST(TilemapTest, GetGlobalBoundsReturnsDefaultConstructedRect)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getGlobalBounds(), jt::Rect {});
}

TEST(TilemapTest, GetLocalBoundsReturnsDefaultConstructedRect)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getLocalBounds(), jt::Rect {});
}

TEST(TilemapObjectGroupsTest, CountIsZeroForNonExistingLayer)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().count("abcd"), 0);
}

TEST(TilemapObjectGroupsTest, CountIsOneForExistingObjectLayer)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().count("objects"), 1);
}

TEST(TilemapObjectGroupsTest, AmountOfObjectsInObjectGroupIsCorrect)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").size(), 1U);
}

TEST(TilemapObjectGroupsTest, ObjectTypeIsParsedCorrectly)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).type, "type1");
}

TEST(TilemapObjectGroupsTest, ObjectNameIsParsedCorrectly)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).name, "object1");
}

TEST(TilemapObjectGroupsTest, ObjectPositionIsParsedCorrectly)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.x(), 256);
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.y(), 128);
}

TEST(TilemapObjectGroupsTest, ObjectSizeIsParsedCorrectly)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.x(), 64);
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.y(), 96);
}

TEST(TilemapObjectGroupsTest, ObjectRotationIsParsedCorrectly)
{
    jt::Tilemap tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).rotation, 45);
}
