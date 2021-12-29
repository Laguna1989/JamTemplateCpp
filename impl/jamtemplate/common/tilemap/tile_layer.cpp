#include "tile_layer.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "shape.hpp"
#include <memory>

namespace jt {
namespace tilemap {

TileLayer::TileLayer(std::vector<TileInfo> const& tileInfo, std::vector<jt::Sprite> tileSetSprites)
    : m_tileSetSprites { tileSetSprites }
    , m_tiles { tileInfo }
{
}

TileLayer::TileLayer(std::tuple<std::vector<TileInfo> const&, std::vector<jt::Sprite>> mapInfo)
    : TileLayer { std::get<0>(mapInfo), std::get<1>(mapInfo) }
{
}

bool TileLayer::isTileVisible(TileInfo const& tile) const
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
    if (tile.position.x + camOffset.x >= this->m_screenSizeHint.x + tile.size.x) {
        return false;
    }
    if (tile.position.y + camOffset.y >= this->m_screenSizeHint.y + tile.size.y) {
        return false;
    }
    return true;
}

void TileLayer::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (!sptr) {
        return;
    }

    auto const posOffset = m_position + getShakeOffset() + getOffset();
    for (auto const& tile : m_tiles) {
        // optimization: don't draw tiles which are not visible in this frame
        if (!isTileVisible(tile)) {
            continue;
        }

        auto const pixelPosForTile = tile.position + posOffset;
        auto const id = tile.id;
        this->m_tileSetSprites.at(id).setPosition(jt::Vector2f {
            pixelPosForTile.x * this->m_scale.x, pixelPosForTile.y * this->m_scale.y });
        this->m_tileSetSprites.at(id).setScale(this->m_scale);
        this->m_tileSetSprites.at(id).update(0.0f);
        this->m_tileSetSprites.at(id).draw(sptr);
    }
}

void TileLayer::doDrawFlash(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const { }
void TileLayer::doDrawShadow(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const { }

void TileLayer::doUpdate(float /*elapsed*/) { }

void TileLayer::setColor(jt::Color const& col)
{
    for (auto& ts : m_tileSetSprites) {
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

} // namespace tilemap

} // namespace jt
