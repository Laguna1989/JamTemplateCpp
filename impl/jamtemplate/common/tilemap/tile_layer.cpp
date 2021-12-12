#include "tile_layer.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "shape.hpp"
#include <memory>

namespace jt {
namespace tilemap {

TileLayer::TileLayer(std::string const& path,
    std::shared_ptr<jt::TilemapManagerInterface> tilemapManager, std::string const& layerName,
    std::shared_ptr<jt::TextureManagerInterface> textureManager)
{
    if (tilemapManager == nullptr) {
        throw std::invalid_argument { "nullptr tilemapManager is not supported" };
    }

    m_position = jt::Vector2f { 0.0f, 0.0f };
    m_screenSizeHint = jt::Vector2f { 0.0f, 0.0f };
    m_textureManager = textureManager;

    auto& map = tilemapManager->getMap(path);

    loadTilesetSprites(map);

    loadTilemap(map, layerName);

    m_mapSizeInZiles = jt::Vector2u { static_cast<unsigned int>(map->getSize().x),
        static_cast<unsigned int>(map->getSize().y) };
}
void TileLayer::loadTilemap(std::unique_ptr<tson::Map>& map, std::string const& layerName)
{
    for (auto& layer : map->getLayers()) {
        // skip all non-tile layers
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }
        if (layer.getName() == layerName) {
            for (auto& [_, tile] : layer.getTileObjects()) {
                parseSingleTile(tile);
            }
        }
    }
}

void TileLayer::parseSingleTile(tson::TileObject& tile)
{
    checkIdBounds(tile);

    auto const pos = Conversion::vec(tile.getPosition());
    auto const size = Conversion::vec(tile.getTile()->getTileSize());
    auto const id = static_cast<int>(tile.getTile()->getId()) - 1;

    m_tiles.emplace_back(Tile { pos, size, id });
}

void TileLayer::loadTilesetSprites(std::unique_ptr<tson::Map>& map)
{
    auto const tileset = map->getTilesets().at(0);
    auto const columns = tileset.getColumns();
    auto const rows = tileset.getTileCount() / columns;
    auto const ts = tileset.getTileSize();
    auto const tilesetName = "assets/" + tileset.getImagePath().string();
    m_tileSprites.resize(static_cast<size_t>(rows) * static_cast<size_t>(columns));
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            {
                Sprite tile { tilesetName, Recti { i * ts.x, j * ts.y, ts.x, ts.y },
                    m_textureManager };
                tile.setIgnoreCamMovement(false);
                m_tileSprites.at(i + j * columns) = tile;
            }
        }
    }
}

bool TileLayer::skipCurrentTile(Tile const& tile, jt::Vector2f const& posOffset) const
{
    if (m_screenSizeHint.x == 0 && m_screenSizeHint.y == 0) {
        return false;
    }

    jt::Vector2f const camOffset = getStaticCamOffset();
    if (tile.position.x + camOffset.x + tile.size.x < 0) {
        return true;
    }
    if (tile.position.y + camOffset.y + tile.size.y < 0) {
        return true;
    }
    if (tile.position.x + camOffset.x >= this->m_screenSizeHint.x + tile.size.x) {
        return true;
    }
    if (tile.position.y + camOffset.y >= this->m_screenSizeHint.y + tile.size.y) {
        return true;
    }
    return false;
}

void TileLayer::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (!sptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset();
    for (auto const& tile : m_tiles) {
        // optimization: don't draw tiles outside the game window
        if (skipCurrentTile(tile, posOffset)) {
            continue;
        }
        auto const pixelPosForTile = tile.position + posOffset;
        auto const id = tile.id;
        this->m_tileSprites.at(id).setPosition(jt::Vector2f {
            pixelPosForTile.x * this->m_scale.x, pixelPosForTile.y * this->m_scale.y });
        this->m_tileSprites.at(id).setScale(this->m_scale);
        this->m_tileSprites.at(id).update(0.0f);
        this->m_tileSprites.at(id).draw(sptr);
    }
}

void TileLayer::checkIdBounds(tson::TileObject& tile) const
{
    auto const rawId = tile.getTile()->getId();
    if (rawId == 1 || rawId + 1 >= m_tileSprites.size()) {
        throw std::invalid_argument { "Invalid tile id in map" };
    }
}

void TileLayer::doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }
void TileLayer::doDrawShadow(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }

void TileLayer::doUpdate(float /*elapsed*/) { }

void TileLayer::setColor(jt::Color const& col)
{
    for (auto& ts : m_tileSprites) {
        ts.setColor(col);
    }
    m_color = col;
}
jt::Color TileLayer::getColor() const { return m_color; }

void TileLayer::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f TileLayer::getPosition() const { return m_position; }

jt::Rectf TileLayer::getGlobalBounds() const { return jt::Rectf {}; }
jt::Rectf TileLayer::getLocalBounds() const { return jt::Rectf {}; }

void TileLayer::setFlashColor(jt::Color const& col) { m_flashColor = col; }
jt::Color TileLayer::getFlashColor() const { return m_flashColor; }

void TileLayer::setScale(jt::Vector2f const& scale) { m_scale = scale; }
jt::Vector2f TileLayer::getScale() const { return m_scale; }

void TileLayer::setOrigin(jt::Vector2f const& origin) { m_origin = origin; }
jt::Vector2f TileLayer::getOrigin() const { return m_origin; }

void TileLayer::doRotate(float /*rot*/) { }

void TileLayer::setScreenSizeHint(jt::Vector2f const& hint) { m_screenSizeHint = hint; }

jt::Vector2u TileLayer::getMapSizeInTiles() { return m_mapSizeInZiles; }

} // namespace tilemap

} // namespace jt
