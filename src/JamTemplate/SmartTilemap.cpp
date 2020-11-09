#include "SmartTilemap.hpp"
#include "Conversions.hpp"
#include "Game.hpp"
#include "SmartObject.hpp"
#include "TextureManager.hpp"

namespace JamTemplate {

SmartTilemap::SmartTilemap(std::filesystem::path const& path)
{
    m_position = sf::Vector2f { 0.0f, 0.0f };
    m_screenSizeHint = sf::Vector2f { 0.0f, 0.0f };

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
    auto const imageSize = tileset.getImageSize();
    auto const ts = tileset.getTileSize();
    auto const tilesetName = "assets/" + tileset.getImagePath().string();
    for (int j = 0; j != rows; ++j) {
        for (int i = 0; i != columns; ++i) {
            m_tileSprites.emplace_back(std::make_unique<sf::Sprite>(
                TextureManager::get(tilesetName), sf::IntRect(i * ts.x, j * ts.y, ts.x, ts.y)));
        }
    }
    for (auto& layer : m_map->getLayers()) {
        const std::string currentGroupName = layer.getName();
        for (auto& obj : layer.getObjects()) {

            Rect collider { C::vec(obj.getPosition()), C::vec(obj.getSize()), obj.getRotation(),
                obj.getType() };
            m_objectGroups[currentGroupName].push_back(collider);
        }
    }
}

void SmartTilemap::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
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

                auto const tilePos = C::vec(tile.getPosition());
                // optimization: don't draw tiles outside the game window
                if (g) {
                    sf::Vector2f const camoffset
                        = (getIgnoreCamMovement() ? sf::Vector2f { 0.0f, 0.0f }
                                                  : g->getCamOffset());

                    auto const px = tilePos.x;
                    auto const py = tilePos.y;
                    auto const tsx = tile.getTile()->getTileSize().x;
                    auto const tsy = tile.getTile()->getTileSize().y;
                    if (px - camoffset.x + tsx < 0) {
                        continue;
                    }
                    if (py - camoffset.y + tsy < 0) {
                        continue;
                    }
                    if (px - camoffset.x >= m_screenSizeHint.x + tsx) {
                        continue;
                    }
                    if (py - camoffset.y >= m_screenSizeHint.y + tsy) {
                        continue;
                    }
                }
                auto const pixelPosForTile = tilePos + posOffset;
                m_tileSprites.at(id)->setPosition(pixelPosForTile);
                sptr->draw(*m_tileSprites.at(id));
            }
        }

        sf::RectangleShape shape(sf::Vector2f(1.0f, 1.0f));
        for (auto& objLayer : m_objectGroups) {
            for (auto& obj : objLayer.second) {
                shape.setSize(obj.sizeDiagonal);
                shape.setPosition(obj.position);
                shape.setRotation(obj.rotation);
                if (m_highlightObjectGroups) {
                    shape.setOutlineColor(JamTemplate::Random::getRandomColor());
                } else {
                    shape.setOutlineColor(sf::Color::Transparent);
                }
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineThickness(2.0f);
                sptr->draw(shape);
            }
        }
    }
}

void SmartTilemap::doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const { }
void SmartTilemap::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const { }

void SmartTilemap::doUpdate(float /*elapsed*/) { }

void SmartTilemap::setColor(sf::Color const& col)
{
    for (auto& ts : m_tileSprites) {
        ts->setColor(col);
    }
}
const sf::Color SmartTilemap::getColor() const { return sf::Color::Black; }

void SmartTilemap::setPosition(sf::Vector2f const& pos) { m_position = pos; }
const sf::Vector2f SmartTilemap::getPosition() const { return m_position; }

sf::Transform const SmartTilemap::getTransform() const { return sf::Transform {}; }
sf::FloatRect const SmartTilemap::getGlobalBounds() const { return sf::FloatRect {}; }
sf::FloatRect const SmartTilemap::getLocalBounds() const { return sf::FloatRect {}; }

void SmartTilemap::setFlashColor(sf::Color const& /*col*/)
{
    throw std::logic_error { "flash not supported by SmartBar" };
}
const sf::Color SmartTilemap::getFlashColor() const { return sf::Color::Black; }

void SmartTilemap::setScale(sf::Vector2f const& /*scale*/) { }
const sf::Vector2f SmartTilemap::getScale() const { return sf::Vector2f {}; }

void SmartTilemap::setOrigin(sf::Vector2f const& /*origin*/) { }
const sf::Vector2f SmartTilemap::getOrigin() const { return sf::Vector2f {}; }

void SmartTilemap::doRotate(float /*rot*/) { }

void SmartTilemap::setScreenSizeHint(sf::Vector2f const& hint, std::shared_ptr<Game> ptr)
{
    m_screenSizeHint = hint;
    m_gamePtr = ptr;
}

const sf::Vector2i SmartTilemap::getMapSizeInTiles()
{
    return sf::Vector2i { m_map->getSize().x, m_map->getSize().y };
}

} // namespace JamTemplate
