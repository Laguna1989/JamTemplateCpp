#include "tilemap/object_layer.hpp"
#include "tilemap/tilemap_manager_tileson_impl.hpp"
#include <gtest/gtest.h>

using ::jt::tilemap::ObjectLayer;

TEST(TilemapObjectLayerTest, JsonDoesContainObjectGroups)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };

    ASSERT_FALSE(ol.getObjects().empty());
}

TEST(TilemapObjectLayerTest, NonExistingLayerDoesNotContainObjects)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "non_existing_object_layer" };
    ASSERT_EQ(ol.getObjects().size(), 0);
}

TEST(TilemapObjectLayerTest, ExistingLayerDoesContainObjects)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().size(), 5);
}

TEST(TilemapObjectLayerTest, ObjectTypeIsParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).type, "type1");
}

TEST(TilemapObjectLayerTest, ObjectNameIsParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).name, "object1");
}

TEST(TilemapObjectLayerTest, ObjectPositionIsParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).position.x, 256);
    ASSERT_EQ(ol.getObjects().at(0).position.y, 128);
}

TEST(TilemapObjectLayerTest, ObjectSizeIsParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).size.x, 64);
    ASSERT_EQ(ol.getObjects().at(0).size.y, 96);
}

TEST(TilemapObjectLayerTest, ObjectRotationIsParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).rotation, 45);
}

TEST(TilemapObjectLayerTest, BoolPropertyParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.bools.at("bool_prop"), false);
}

TEST(TilemapObjectLayerTest, FloatPropertyParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_FLOAT_EQ(ol.getObjects().at(0).properties.floats.at("float_prop"), 1337.42f);
}

TEST(TilemapObjectLayerTest, IntPropertyParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.ints.at("int_prop"), 1234);
}

TEST(TilemapObjectLayerTest, StringPropertyParsedCorrectly)
{
    auto tilemapManager = std::make_shared<jt::TilemapManagerTilesonImpl>();
    ObjectLayer ol { "assets/tileson_test.json", tilemapManager, "objects" };
    ASSERT_EQ(ol.getObjects().at(0).properties.strings.at("string_prop"), "abcd");
}
