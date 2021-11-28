#include "tilemap/object_layer.hpp"
#include <gtest/gtest.h>

using ::jt::tilemap::ObjectLayer;

TEST(TilemapObjectLayerTest, JsonDoesContainObjectGroups)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };

    ASSERT_FALSE(ol.getObjects().empty());
}

TEST(TilemapObjectLayerTest, NonExistingLayerDoesNotContainObjects)
{
    ObjectLayer ol { "assets/tileson_test.json", "non_existing_object_layer" };
    ASSERT_EQ(ol.getObjects().size(), 0);
}

TEST(TilemapObjectLayerTest, ExistingLayerDoesContainObjects)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().size(), 5);
}

TEST(TilemapObjectLayerTest, ObjectTypeIsParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).type, "type1");
}

TEST(TilemapObjectLayerTest, ObjectNameIsParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).name, "object1");
}

TEST(TilemapObjectLayerTest, ObjectPositionIsParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).position.x(), 256);
    ASSERT_EQ(ol.getObjects().at(0).position.y(), 128);
}

TEST(TilemapObjectLayerTest, ObjectSizeIsParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).size.x(), 64);
    ASSERT_EQ(ol.getObjects().at(0).size.y(), 96);
}

TEST(TilemapObjectLayerTest, ObjectRotationIsParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).rotation, 45);
}

TEST(TilemapObjectLayerTest, BoolPropertyParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.bools.at("bool_prop"), false);
}

TEST(TilemapObjectLayerTest, FloatPropertyParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_FLOAT_EQ(ol.getObjects().at(0).properties.floats.at("float_prop"), 1337.42f);
}

TEST(TilemapObjectLayerTest, IntPropertyParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.ints.at("int_prop"), 1234);
}

TEST(TilemapObjectLayerTest, StringPropertyParsedCorrectly)
{
    ObjectLayer ol { "assets/tileson_test.json", "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.strings.at("string_prop"), "abcd");
}
