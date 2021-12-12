#include "tilemap/object_layer.hpp"
#include "tilemap/tilemap_manager_tileson_impl.hpp"
#include "tilemap/tileson_loader.hpp"
#include <gtest/gtest.h>

using ::jt::tilemap::ObjectLayer;

ObjectLayer getValidObjectLayer()
{
    jt::tilemap::TilesonLoader loader { "assets/tileson_test.json" };
    return ObjectLayer { loader.loadObjectsFromLayer("objects") };
}

ObjectLayer getInvalidObjectLayer()
{
    jt::tilemap::TilesonLoader loader { "assets/tileson_test.json" };
    return ObjectLayer { loader.loadObjectsFromLayer("blarz__non_existing__Blurz") };
}

class TilemapObjectLayerTestFromFile : public ::testing::Test {
public:
    std::unique_ptr<jt::tilemap::ObjectLayer> objectLayer;
    void SetUp() override
    {
        objectLayer = std::make_unique<jt::tilemap::ObjectLayer>(getValidObjectLayer());
    }
};

TEST_F(TilemapObjectLayerTestFromFile, JsonDoesContainObjectGroups)
{
    ASSERT_FALSE(objectLayer->getObjects().empty());
}

TEST_F(TilemapObjectLayerTestFromFile, NonExistingLayerDoesNotContainObjects)
{
    objectLayer = std::make_unique<jt::tilemap::ObjectLayer>(getInvalidObjectLayer());
    ASSERT_EQ(objectLayer->getObjects().size(), 0);
}

TEST_F(TilemapObjectLayerTestFromFile, ExistingLayerDoesContainObjects)
{
    ASSERT_EQ(objectLayer->getObjects().size(), 5);
}

TEST_F(TilemapObjectLayerTestFromFile, ObjectTypeIsParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).type, "type1");
}

TEST_F(TilemapObjectLayerTestFromFile, ObjectNameIsParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).name, "object1");
}

TEST_F(TilemapObjectLayerTestFromFile, ObjectPositionIsParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).position.x, 256);
    ASSERT_EQ(objectLayer->getObjects().at(0).position.y, 128);
}

TEST_F(TilemapObjectLayerTestFromFile, ObjectSizeIsParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).size.x, 64);
    ASSERT_EQ(objectLayer->getObjects().at(0).size.y, 96);
}

TEST_F(TilemapObjectLayerTestFromFile, ObjectRotationIsParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).rotation, 45);
}

TEST_F(TilemapObjectLayerTestFromFile, BoolPropertyParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).properties.bools.at("bool_prop"), false);
}

TEST_F(TilemapObjectLayerTestFromFile, FloatPropertyParsedCorrectly)
{
    ASSERT_FLOAT_EQ(objectLayer->getObjects().at(0).properties.floats.at("float_prop"), 1337.42f);
}

TEST_F(TilemapObjectLayerTestFromFile, IntPropertyParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).properties.ints.at("int_prop"), 1234);
}

TEST_F(TilemapObjectLayerTestFromFile, StringPropertyParsedCorrectly)
{
    ASSERT_EQ(objectLayer->getObjects().at(0).properties.strings.at("string_prop"), "abcd");
}

TEST(TilemapObjectLayerTest, ConstructorFromListEmpty)
{
    std::vector<jt::tilemap::InfoRect> infoRects {};
    ObjectLayer objectLayer { infoRects };
    ASSERT_TRUE(objectLayer.getObjects().empty());
}

TEST(TilemapObjectLayerTest, ConstructorFromListOneEntry)
{
    jt::tilemap::InfoRect rect {};
    std::vector<jt::tilemap::InfoRect> infoRects { rect };
    ObjectLayer objectLayer { infoRects };
    ASSERT_FALSE(objectLayer.getObjects().empty());
}
