#include "tilemap/objectlayer.hpp"
#include <gtest/gtest.h>

using ::jt::tilemap::ObjectLayer;

TEST(TilemapObjectLayerTest, JsonDoesContainObjectGroups)
{
    ObjectLayer tm { "assets/tileson_test.json" };

    ASSERT_FALSE(tm.getObjectGroups().empty());
}

TEST(TilemapObjectLayerTest, CountIsZeroForNonExistingLayer)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().count("abcd"), 0);
}

TEST(TilemapObjectLayerTest, CountIsOneForExistingObjectLayer)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().count("objects"), 1);
}

TEST(TilemapObjectLayerTest, AmountOfObjectsInObjectGroupIsCorrect)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").size(), 1U);
}

TEST(TilemapObjectLayerTest, ObjectTypeIsParsedCorrectly)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).type, "type1");
}

TEST(TilemapObjectLayerTest, ObjectNameIsParsedCorrectly)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).name, "object1");
}

TEST(TilemapObjectLayerTest, ObjectPositionIsParsedCorrectly)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.x(), 256);
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).position.y(), 128);
}

TEST(TilemapObjectLayerTest, ObjectSizeIsParsedCorrectly)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.x(), 64);
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).size.y(), 96);
}

TEST(TilemapObjectLayerTest, ObjectRotationIsParsedCorrectly)
{
    ObjectLayer tm { "assets/tileson_test.json" };
    ASSERT_EQ(tm.getObjectGroups().at("objects").at(0).rotation, 45);
}
