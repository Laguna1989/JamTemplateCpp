#include "tilelayer.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "shape.hpp"
#include <iostream>
#include <memory>

namespace jt {
namespace tilemap {
TileLayer::TileLayer(std::string const& path, std::string const& layerName)
{
    m_layerName = layerName;
    m_position = jt::Vector2 { 0.0f, 0.0f };
    m_screenSizeHint = jt::Vector2 { 0.0f, 0.0f };

    tson::Tileson parser;

    m_map = parser.parse(path);
    if (m_map->getStatus() != tson::ParseStatus::OK) {
        std::cout << "tilemap json could not be parsed.\n";
        throw std::invalid_argument { "tilemap json could not be parsed." };
    }

    auto const tileset = m_map->getTilesets().at(0);
    auto const columns = tileset.getColumns();
    auto const rows = tileset.getTileCount() / columns;
    auto const ts = tileset.getTileSize();
    auto const tilesetName = "assets/" + tileset.getImagePath().string();
    m_tileSprites.resize(static_cast<std::size_t>(rows) * static_cast<std::size_t>(columns));
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            {
                jt::Sprite tile {};
                tile.loadSprite(tilesetName, jt::Recti(i * ts.x, j * ts.y, ts.x, ts.y));
                tile.setIgnoreCamMovement(false);
                m_tileSprites.at(i + j * columns) = tile;
            }
        }
    }
}
/*


*/

void TileLayer::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (!sptr) {
        return;
    }

    if (m_map == nullptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset();

    for (auto& layer : m_map->getLayers()) {
        // skip all non-tile layers
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }
        if (layer.getName() == m_layerName) {
            drawSingleTileLayer(sptr, posOffset, layer);
        }
    }
}

void TileLayer::drawSingleTileLayer(
    std::shared_ptr<jt::renderTarget> const& rt, Vector2 const& posOffset, tson::Layer& layer) const
{
    for (auto& [pos, tile] : layer.getTileObjects()) {
        this->checkIdBounds(tile);

        auto const tilePos = Conversion::vec(tile.getPosition());

        // optimization: don't draw tiles outside the game window
        if (this->m_screenSizeHint.x() != 0 && this->m_screenSizeHint.y() != 0) {
            jt::Vector2 const camOffset = getStaticCamOffset();
            auto const px = tilePos.x();
            auto const py = tilePos.y();
            auto const tsx = tile.getTile()->getTileSize().x;
            auto const tsy = tile.getTile()->getTileSize().y;
            if (px + camOffset.x() + tsx < 0) {
                continue;
            }
            if (py + camOffset.y() + tsy < 0) {
                continue;
            }
            if (px + camOffset.x() >= this->m_screenSizeHint.x() + tsx) {
                continue;
            }
            if (py + camOffset.y() >= this->m_screenSizeHint.y() + tsy) {
                continue;
            }
        }
        auto const pixelPosForTile = tilePos + posOffset;
        auto const id = tile.getTile()->getId() - 1U;
        this->m_tileSprites.at(id).setPosition(jt::Vector2 {
            pixelPosForTile.x() * this->m_scale.x(), pixelPosForTile.y() * this->m_scale.y() });
        this->m_tileSprites.at(id).setScale(this->m_scale);
        this->m_tileSprites.at(id).update(0.0f);
        this->m_tileSprites.at(id).draw(rt);
    }
}

void TileLayer::checkIdBounds(tson::TileObject& tile) const
{
    auto const rawId = tile.getTile()->getId();
    if (rawId == 1 || rawId + 1 >= m_tileSprites.size()) {
        std::cout << "Invalid tile id in map\n";
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

void TileLayer::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 TileLayer::getPosition() const { return m_position; }

jt::Rect TileLayer::getGlobalBounds() const { return jt::Rect {}; }
jt::Rect TileLayer::getLocalBounds() const { return jt::Rect {}; }

void TileLayer::setFlashColor(jt::Color const& col) { m_flashColor = col; }
jt::Color TileLayer::getFlashColor() const { return m_flashColor; }

void TileLayer::setScale(jt::Vector2 const& scale) { m_scale = scale; }
jt::Vector2 TileLayer::getScale() const { return m_scale; }

void TileLayer::setOrigin(jt::Vector2 const& origin) { m_origin = origin; }
jt::Vector2 TileLayer::getOrigin() const { return m_origin; }

void TileLayer::doRotate(float /*rot*/) { }

void TileLayer::setScreenSizeHint(jt::Vector2 const& hint) { m_screenSizeHint = hint; }

jt::Vector2u TileLayer::getMapSizeInTiles()
{
    return jt::Vector2u { static_cast<unsigned int>(m_map->getSize().x),
        static_cast<unsigned int>(m_map->getSize().y) };
}

} // namespace tilemap

} // namespace jt
