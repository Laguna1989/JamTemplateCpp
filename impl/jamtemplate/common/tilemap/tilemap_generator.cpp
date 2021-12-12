#include "tilemap_generator.hpp"
#include "random/random.hpp"

namespace jt {
namespace tilemap {
std::tuple<std::vector<TileInfo>, std::vector<jt::Sprite>> TilemapGenerator::createRandomMap(
    std::string const& layerName, std::shared_ptr<jt::TextureManagerInterface> textureManager)
{

    jt::Vector2u ts { 48, 48 };

    auto const tilesetName = "assets/uf_terrain.png";
    jt::Sprite spr { tilesetName, textureManager };
    jt::Vector2u imageSizeInPixel { static_cast<unsigned int>(spr.getLocalBounds().width),
        static_cast<unsigned int>(spr.getLocalBounds().height) };

    auto const columns = imageSizeInPixel.x / ts.x;
    auto const rows = imageSizeInPixel.y / ts.y;

    std::vector<jt::Sprite> tileSetSprites;
    tileSetSprites.resize(rows * columns);
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            Sprite tile { tilesetName,
                Recti { static_cast<int>(i * ts.x), static_cast<int>(j * ts.y),
                    static_cast<int>(ts.x), static_cast<int>(ts.y) },
                textureManager };
            tile.setIgnoreCamMovement(false);
            tileSetSprites.at(i + j * columns) = tile;
        }
    }

    std::vector<TileInfo> tiles;
    for (auto i = 0; i != 40; ++i) {
        for (auto j = 0; j != 40; ++j) {
            TileInfo info;
            info.position
                = jt::Vector2f { static_cast<float>(ts.x * i), static_cast<float>(ts.y * j) };
            info.size = jt::Vector2f { static_cast<float>(ts.x), static_cast<float>(ts.y) };
            info.id = jt::Random::getInt(121, 124);
            tiles.push_back(info);
        }
    }

    return std::tuple<std::vector<TileInfo>, std::vector<jt::Sprite>>(tiles, tileSetSprites);
}
} // namespace tilemap
} // namespace jt
