#include "Tilemap.hpp"
#include "Conversions.hpp"
#include "GameInterface.hpp"
#include <memory>

namespace jt {

Tilemap::Tilemap(std::string const& path)
{
    m_position = jt::Vector2 { 0.0f, 0.0f };
    m_screenSizeHint = jt::Vector2 { 0.0f, 0.0f };

    tson::Tileson parser;

    m_map = parser.parse(path);
    if (m_map->getStatus() != tson::ParseStatus::OK) {
        std::cout << "tileson test could not be parsed.\n";
        throw std::logic_error { "tileson test could not be parsed." };
    }

    if (m_map->getTilesets().empty()) {
        std::cout << "tileson test could not be parsed.\n";
        throw std::invalid_argument { "empty tilesets" };
    }
    auto const tileset = m_map->getTilesets().at(0);
    // // std::cout << "tileset image path: " << tileset.getImagePath() << std::endl;
    auto const columns = tileset.getColumns();
    auto const rows = tileset.getTileCount() / columns;
    auto const ts = tileset.getTileSize();
    auto const tilesetName = "assets/" + tileset.getImagePath();
    m_tileSprites.resize(rows * columns);
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            jt::Sprite tile {};
            tile.loadSprite(tilesetName, jt::Recti(i * ts.x, j * ts.y, ts.x, ts.y));
            tile.setIgnoreCamMovement(false);
            m_tileSprites.at(i + j * columns) = tile;
        }
    }
    // for (auto& layer : m_map->getLayers()) {
    //     const std::string currentGroupName = layer.getName();
    //     for (auto& obj : layer.getObjects()) {

    //         InfoRect collider { Conversion::vec(obj.getPosition()),
    //         Conversion::vec(obj.getSize()),
    //             obj.getRotation(), obj.getType() };
    //         m_objectGroups[currentGroupName].push_back(collider);
    //     }
    // }
#if ENABLE_WEB
    setIgnoreCamMovement(true);
#else
    setIgnoreCamMovement(true);
#endif
}

void Tilemap::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (m_map == nullptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset();
    // std::cout << "Tilemap.posOffset.x " << posOffset.x() << std::endl;

    auto g = m_gamePtr.lock();

    for (auto& layer : m_map->getLayers()) {
        // skip all non-tile layers.
        if (layer.getType() != tson::LayerType::TileLayer) {
            continue;
        }

        for (auto& [pos, tile] : layer.getTileObjects()) {
            checkIdBounds(tile);

            auto const tilePos = Conversion::vec(tile.getPosition());
            // optimization: don't draw tiles outside the game window
            if (g) {
                jt::Vector2 const camoffset = getStaticCamOffset();
                // std::cout << camoffset.x() << std::endl;
                auto const px = tilePos.x();
                auto const py = tilePos.y();
                auto const tsx = tile.getTile()->getTileSize().x;
                auto const tsy = tile.getTile()->getTileSize().y;
                if (px + camoffset.x() + tsx < 0) {
                    continue;
                }
                if (py + camoffset.y() + tsy < 0) {
                    continue;
                }
                if (px + camoffset.x() >= m_screenSizeHint.x() + tsx) {
                    continue;
                }
                if (py + camoffset.y() >= m_screenSizeHint.y() + tsy) {
                    continue;
                }
            }
            auto const pixelPosForTile = tilePos + posOffset;
            auto const id = tile.getTile()->getId() - 1U;
            m_tileSprites.at(id).setPosition(pixelPosForTile);
            m_tileSprites.at(id).update(0.0f);
            m_tileSprites.at(id).draw(sptr);
        }
    }
}

void Tilemap::checkIdBounds(const tson::TileObject& tile) const
{
    auto const rawId = tile.getTile()->getId();
    if (rawId == 1 || rawId + 1 >= m_tileSprites.size()) {
        std::cout << "Invalid tile id in map\n";
        throw std::invalid_argument { "Invalid tile id in map" };
    }
}

void Tilemap::doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }
void Tilemap::doDrawShadow(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }

void Tilemap::doUpdate(float /*elapsed*/) { }

void Tilemap::setColor(jt::Color const& col)
{
    for (auto& ts : m_tileSprites) {
        ts.setColor(col);
    }
}
const jt::Color Tilemap::getColor() const { return jt::colors::Black; }

void Tilemap::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 Tilemap::getPosition() const { return m_position; }

// sf::Transform const Tilemap::getTransform() const { return sf::Transform {}; }
jt::Rect const Tilemap::getGlobalBounds() const { return jt::Rect {}; }
jt::Rect const Tilemap::getLocalBounds() const { return jt::Rect {}; }

void Tilemap::setFlashColor(jt::Color const& /*col*/)
{
    throw std::logic_error { "flash not supported by Bar" };
}
const jt::Color Tilemap::getFlashColor() const { return jt::colors::Black; }

void Tilemap::setScale(jt::Vector2 const& /*scale*/) { }
const jt::Vector2 Tilemap::getScale() const { return jt::Vector2 {}; }

void Tilemap::setOrigin(jt::Vector2 const& /*origin*/) { }
const jt::Vector2 Tilemap::getOrigin() const { return jt::Vector2 {}; }

void Tilemap::doRotate(float /*rot*/) { }

void Tilemap::setScreenSizeHint(jt::Vector2 const& hint, std::shared_ptr<GameInterface> ptr)
{
    m_screenSizeHint = hint;
    m_gamePtr = ptr;
}

const jt::Vector2u Tilemap::getMapSizeInTiles()
{
    return jt::Vector2u { static_cast<unsigned int>(m_map->getSize().x),
        static_cast<unsigned int>(m_map->getSize().y) };
}

} // namespace jt
