#include "SmartTilemap.hpp"
#include "Conversions.hpp"
#include "GameBase.hpp"
#include "TextureManager.hpp"
#include <memory>

namespace jt {

SmartTilemap::SmartTilemap(std::string const& path)
{
    m_position = jt::Vector2 { 0.0f, 0.0f };
    m_screenSizeHint = jt::Vector2 { 0.0f, 0.0f };

    tson::Tileson parser;

    m_map = parser.parse(path);

    if (m_map->getStatus() != tson::ParseStatus::OK) {
        throw std::logic_error { "tileson test could not be parsed." };
    }

    if (m_map->getTilesets().empty()) {
        throw std::invalid_argument { "empty tilesets" };
    }
    auto const tileset = m_map->getTilesets().at(0);
    // std::cout << "tileset image path: " << tileset.getImagePath() << std::endl;

    auto const columns = tileset.getColumns();
    auto const rows = tileset.getTileCount() / columns;
    auto const ts = tileset.getTileSize();
    auto const tilesetName = "assets/" + tileset.getImagePath();
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            auto const tile = std::make_shared<jt::SmartSprite>();
            tile->loadSprite(tilesetName, jt::Recti(i * ts.x, j * ts.y, ts.x, ts.y));
            m_tileSprites.emplace_back(tile);
        }
    }
    for (auto& layer : m_map->getLayers()) {
        const std::string currentGroupName = layer.getName();
        for (auto& obj : layer.getObjects()) {

            InfoRect collider { Conversion::vec(obj.getPosition()), Conversion::vec(obj.getSize()),
                obj.getRotation(), obj.getType() };
            m_objectGroups[currentGroupName].push_back(collider);
        }
    }
}

void SmartTilemap::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (m_map == nullptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset() + getCamOffset();

    auto g = m_gamePtr.lock();

    for (auto& layer : m_map->getLayers()) {
        if (layer.getType() == tson::LayerType::TileLayer) {

            for (auto& [pos, tile] : layer.getTileObjects()) {

                auto const id = tile.getTile()->getId() - 1;
                if (id < 0 || id >= m_tileSprites.size()) {
                    throw std::invalid_argument { "Invalid tile id in map" };
                }

                auto const tilePos = Conversion::vec(tile.getPosition());
                // optimization: don't draw tiles outside the game window
                if (g) {
                    jt::Vector2 const camoffset
                        = (getIgnoreCamMovement() ? jt::Vector2 { 0.0f, 0.0f } : g->getCamOffset());

                    auto const px = tilePos.x();
                    auto const py = tilePos.y();
                    auto const tsx = tile.getTile()->getTileSize().x;
                    auto const tsy = tile.getTile()->getTileSize().y;
                    if (px - camoffset.x() + tsx < 0) {
                        continue;
                    }
                    if (py - camoffset.y() + tsy < 0) {
                        continue;
                    }
                    if (px - camoffset.x() >= m_screenSizeHint.x() + tsx) {
                        continue;
                    }
                    if (py - camoffset.y() >= m_screenSizeHint.y() + tsy) {
                        continue;
                    }
                }
                auto const pixelPosForTile = tilePos + posOffset;
                m_tileSprites.at(id)->setPosition(pixelPosForTile);
                m_tileSprites.at(id)->update(0.0f);
                m_tileSprites.at(id)->draw(sptr);
            }
        }

        // TODO
        // sf::RectangleShape shape(jt::Vector2(1.0f, 1.0f));
        // for (auto& objLayer : m_objectGroups) {
        //     for (auto& obj : objLayer.second) {
        //         shape.setSize(obj.sizeDiagonal);
        //         shape.setPosition(obj.position);
        //         shape.setRotation(obj.rotation);
        //         if (m_highlightObjectGroups) {
        //             shape.setOutlineColor(jt::Random::getRandomColor());
        //         } else {
        //             shape.setOutlineColor(jt::colors::Transparent);
        //         }
        //         shape.setFillColor(jt::colors::Transparent);
        //         shape.setOutlineThickness(2.0f);
        //         sptr->draw(shape);
        //     }
        // }
    }
}

void SmartTilemap::doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const { }
void SmartTilemap::doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const { }

void SmartTilemap::doUpdate(float /*elapsed*/) { }

void SmartTilemap::setColor(jt::Color const& col)
{
    for (auto& ts : m_tileSprites) {
        ts->setColor(col);
    }
}
const jt::Color SmartTilemap::getColor() const { return jt::colors::Black; }

void SmartTilemap::setPosition(jt::Vector2 const& pos) { m_position = pos; }
const jt::Vector2 SmartTilemap::getPosition() const { return m_position; }

// sf::Transform const SmartTilemap::getTransform() const { return sf::Transform {}; }
jt::Rect const SmartTilemap::getGlobalBounds() const { return jt::Rect {}; }
jt::Rect const SmartTilemap::getLocalBounds() const { return jt::Rect {}; }

void SmartTilemap::setFlashColor(jt::Color const& /*col*/)
{
    throw std::logic_error { "flash not supported by SmartBar" };
}
const jt::Color SmartTilemap::getFlashColor() const { return jt::colors::Black; }

void SmartTilemap::setScale(jt::Vector2 const& /*scale*/) { }
const jt::Vector2 SmartTilemap::getScale() const { return jt::Vector2 {}; }

void SmartTilemap::setOrigin(jt::Vector2 const& /*origin*/) { }
const jt::Vector2 SmartTilemap::getOrigin() const { return jt::Vector2 {}; }

void SmartTilemap::doRotate(float /*rot*/) { }

void SmartTilemap::setScreenSizeHint(jt::Vector2 const& hint, std::shared_ptr<GameBase> ptr)
{
    m_screenSizeHint = hint;
    m_gamePtr = ptr;
}

const jt::Vector2u SmartTilemap::getMapSizeInTiles()
{
    return jt::Vector2u { static_cast<unsigned int>(m_map->getSize().x),
        static_cast<unsigned int>(m_map->getSize().y) };
}

} // namespace jt
