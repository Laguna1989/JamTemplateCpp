#include "Tilemap.hpp"
#include "Conversions.hpp"
#include "Game.hpp"
#include "SmartObject.hpp"
#include "TextureManager.hpp"

namespace JamTemplate {

Tilemap::Tilemap(std::filesystem::path const& path)
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
    std::cout << "tileset image path: " << tileset.getImagePath() << std::endl;

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
}

void Tilemap::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    if (m_map == nullptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset();

    auto g = m_gamePtr.lock();
    sf::Vector2f camoffset {};
    if (g) {
        camoffset = g->getCamOffset();
    }
    std::size_t count { 0 };
    for (auto const& layer : m_map->getLayers()) {
        if (layer.getType() == tson::LayerType::TileLayer) {

            for (auto& [pos, tile] : layer.getTileObjects()) {
                // Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
                // Would be unnecessary otherwise.

                auto const id = tile.getTile()->getId() - 1;

                if (id < 0 || id >= m_tileSprites.size()) {
                    throw std::invalid_argument { "Invalid tile id in map" };
                }

                // optimization: don't draw tiles outside the game window
                if (g) {
                    auto const px = tile.getPosition().x;
                    auto const py = tile.getPosition().y;
                    if (px - camoffset.x + tile.getTile()->getTileSize().x < 0) {
                        continue;
                    }
                    if (py - camoffset.y + tile.getTile()->getTileSize().y < 0) {
                        continue;
                    }
                    if (px - camoffset.x >= m_screenSizeHint.x + tile.getTile()->getTileSize().x) {
                        continue;
                    }
                    if (py - camoffset.y >= m_screenSizeHint.y + tile.getTile()->getTileSize().y) {
                        continue;
                    }
                }
                count++;
                auto const& tileSprite = m_tileSprites.at(id);
                auto const pixelPosForTile = C::vec(tile.getPosition()) + posOffset;
                tileSprite->setPosition(pixelPosForTile);
                sptr->draw(*tileSprite);
            }
        }
    }
}

void Tilemap::doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const { }
void Tilemap::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const { }

void Tilemap::doUpdate(float elapsed) { }

void Tilemap::setColor(sf::Color const& col)
{
    for (auto& ts : m_tileSprites) {
        ts->setColor(col);
    }
}
const sf::Color Tilemap::getColor() const { return sf::Color::Black; }

void Tilemap::setPosition(sf::Vector2f const& pos) { m_position = pos; }
const sf::Vector2f Tilemap::getPosition() const { return m_position; }

sf::Transform const Tilemap::getTransform() const { return sf::Transform {}; }
sf::FloatRect const Tilemap::getGlobalBounds() const { return sf::FloatRect {}; }
sf::FloatRect const Tilemap::getLocalBounds() const { return sf::FloatRect {}; }

void Tilemap::setFlashColor(sf::Color const& col) { }
const sf::Color Tilemap::getFlashColor() const { return sf::Color::Black; }

void Tilemap::setScale(sf::Vector2f const& scale) { }
const sf::Vector2f Tilemap::getScale() const { return sf::Vector2f {}; }

void Tilemap::setOrigin(sf::Vector2f const& origin) { }
const sf::Vector2f Tilemap::getOrigin() const { return sf::Vector2f {}; }

void Tilemap::doRotate(float /*rot*/) { }

void Tilemap::setScreenSizeHint(sf::Vector2f const& hint, std::shared_ptr<Game> ptr)
{
    m_screenSizeHint = hint;
    m_gamePtr = ptr;
}
} // namespace JamTemplate
