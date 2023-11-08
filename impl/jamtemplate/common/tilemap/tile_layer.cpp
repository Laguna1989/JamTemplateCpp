#include "tile_layer.hpp"
#include <drawable_helpers.hpp>
#include <shape.hpp>
#include <memory>

jt::tilemap::TileLayer::TileLayer(std::vector<jt::tilemap::TileInfo> const& tileInfo,
    std::vector<std::shared_ptr<jt::Sprite>> const& tileSetSprites)
    : m_tileSetSprites { tileSetSprites }
    , m_tiles { tileInfo }
{
    calculateMapSize();
}

void jt::tilemap::TileLayer::calculateMapSize()
{
    m_mapSizeInPixel = { 0.0f, 0.0f };
    if (m_tiles.empty()) {
        return;
    }

    for (auto const& t : m_tiles) {
        if (t.position.x > m_mapSizeInPixel.x) {
            m_mapSizeInPixel.x = t.position.x;
        }
        if (t.position.y > m_mapSizeInPixel.y) {
            m_mapSizeInPixel.y = t.position.y;
        }
    }
    m_mapSizeInPixel += m_tiles.at(0).size;
}

jt::tilemap::TileLayer::TileLayer(std::tuple<std::vector<jt::tilemap::TileInfo> const&,
    std::vector<std::shared_ptr<jt::Sprite>>> const& mapInfo)
    : TileLayer { std::get<0>(mapInfo), std::get<1>(mapInfo) }
{
}

bool jt::tilemap::TileLayer::isTileVisible(jt::tilemap::TileInfo const& tile) const
{
    if (m_screenSizeHint.x == 0 && m_screenSizeHint.y == 0) {
        return true;
    }

    jt::Vector2f const camOffset = getStaticCamOffset();
    if (tile.position.x + camOffset.x + tile.size.x < 0) {
        return false;
    }
    if (tile.position.y + camOffset.y + tile.size.y < 0) {
        return false;
    }
    if (tile.position.x + camOffset.x >= m_screenSizeHint.x + tile.size.x) {
        return false;
    }
    if (tile.position.y + camOffset.y >= m_screenSizeHint.y + tile.size.y) {
        return false;
    }
    return true;
}

void jt::tilemap::TileLayer::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    auto const posOffset = m_position + getShakeOffset() + getOffset();
    for (auto const& tile : m_tiles) {
        // optimization: don't draw tiles which are not visible in this frame
        if (!isTileVisible(tile)) {
            continue;
        }

        auto const pixelPosForTile = tile.position + posOffset;
        auto const id = tile.id;
        m_tileSetSprites.at(id)->setPosition(jt::Vector2f { pixelPosForTile.x, pixelPosForTile.y });
        auto color = jt::colors::White;
        if (m_colorFunction != nullptr) {
            color = m_colorFunction(tile.position);
        }
        m_tileSetSprites.at(id)->setColor(color);
        m_tileSetSprites.at(id)->setScale(m_scale);
        m_tileSetSprites.at(id)->update(0.0f);
        m_tileSetSprites.at(id)->setBlendMode(getBlendMode());
        m_tileSetSprites.at(id)->draw(sptr);
    }
}

void jt::tilemap::TileLayer::doDrawFlash(
    std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const
{
}

void jt::tilemap::TileLayer::doDrawShadow(
    std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const
{
    // Nothing to do
}

void jt::tilemap::TileLayer::doDrawOutline(
    std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const
{
    // Nothing to do
}

void jt::tilemap::TileLayer::doUpdate(float /*elapsed*/) { }

void jt::tilemap::TileLayer::setColor(jt::Color const& col)
{
    for (auto& ts : m_tileSetSprites) {
        ts->setColor(col);
    }
    m_color = col;
}

jt::Color jt::tilemap::TileLayer::getColor() const { return m_color; }

void jt::tilemap::TileLayer::setPosition(jt::Vector2f const& pos) { m_position = pos; }

jt::Vector2f jt::tilemap::TileLayer::getPosition() const { return m_position; }

jt::Rectf jt::tilemap::TileLayer::getGlobalBounds() const
{
    return jt::Rectf { getPosition().x, getPosition().y, m_mapSizeInPixel.x, m_mapSizeInPixel.y };
}

jt::Rectf jt::tilemap::TileLayer::getLocalBounds() const
{
    return jt::Rectf { getPosition().x, getPosition().y, m_mapSizeInPixel.x, m_mapSizeInPixel.y };
}

void jt::tilemap::TileLayer::setScale(jt::Vector2f const& scale) { m_scale = scale; }

jt::Vector2f jt::tilemap::TileLayer::getScale() const { return m_scale; }

void jt::tilemap::TileLayer::setOriginInternal(jt::Vector2f const& origin)
{
    for (auto& ts : m_tileSetSprites) {
        ts->setOrigin(origin);
    }
}

void jt::tilemap::TileLayer::doRotate(float rot)
{
    for (auto& ts : m_tileSetSprites) {
        ts->setRotation(rot);
    }
}

void jt::tilemap::TileLayer::setColorFunction(
    std::function<jt::Color(jt::Vector2f const&)> colorFunc)
{
    m_colorFunction = colorFunc;
}

jt::Vector2f jt::tilemap::TileLayer::getMapSizeInPixel() const { return m_mapSizeInPixel; }
