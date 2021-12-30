#ifndef GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
#define GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "drawable_impl.hpp"
#include "info_rect.hpp"
#include "pathfinder/node_interface.hpp"
#include "render_target.hpp"
#include "sprite.hpp"
#include "texture_manager_interface.hpp"
#include "tile_info.hpp"
#include <memory>
#include <vector>

namespace jt {
namespace tilemap {

/// One single tile Layer from a tilemap for drawing
class TileLayer : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<TileLayer>;

    /// Constructor
    /// \param tileInfo tileInfo
    /// \param tileSetSprites Tileset Sprites
    TileLayer(std::vector<TileInfo> const& tileInfo, std::vector<jt::Sprite> tileSetSprites);
    TileLayer(std::tuple<std::vector<TileInfo> const&, std::vector<jt::Sprite>> mapInfo);

    void doDraw(std::shared_ptr<jt::RenderTarget> sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::RenderTarget> sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::RenderTarget> sptr) const override;

    void doUpdate(float elapsed) override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

    void setOrigin(jt::Vector2f const& origin) override;
    jt::Vector2f getOrigin() const override;

    void doRotate(float /*rot*/) override;

    void setScreenSizeHint(jt::Vector2f const& hint);

private:
    mutable std::vector<jt::Sprite> m_tileSetSprites {};

    std::vector<TileInfo> m_tiles {};

    jt::Vector2f m_position { 0.0f, 0.0f };
    jt::Vector2f m_origin { 0.0f, 0.0f };
    jt::Vector2f m_screenSizeHint { 0.0f, 0.0f };
    jt::Vector2f m_scale { 1.0f, 1.0f };
    Color m_color { jt::colors::White };
    Color m_flashColor { jt::colors::White };

    bool isTileVisible(TileInfo const& tile) const;
};

} // namespace tilemap
} // namespace jt

#endif // !GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
