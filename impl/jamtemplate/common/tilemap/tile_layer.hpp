#ifndef JAMTEMPLATE_TILEMAP_HPP
#define JAMTEMPLATE_TILEMAP_HPP

#include <graphics/drawable_impl.hpp>
#include <pathfinder/node_interface.hpp>
#include <render_target_layer.hpp>
#include <sprite.hpp>
#include <texture_manager_interface.hpp>
#include <tilemap/info_rect.hpp>
#include <tilemap/tile_info.hpp>
#include <functional>
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
    TileLayer(std::vector<TileInfo> const& tileInfo,
        std::vector<std::shared_ptr<jt::Sprite>> const& tileSetSprites);

    /// Constructor
    /// \param mapInfo tuple which contains the information for all tiles and sprites of the tilemap
    TileLayer(
        std::tuple<std::vector<TileInfo> const&, std::vector<std::shared_ptr<jt::Sprite>>> const&
            mapInfo);

    void doDraw(std::shared_ptr<jt::RenderTargetLayer> sptr) const override;

    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> sptr) const override;

    /// Get map size in pixel
    //// \returns map size in pixel
    jt::Vector2f getMapSizeInPixel() const;

private:
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;

public:
    void doUpdate(float elapsed) override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    jt::Rectf getLocalBounds() const override;

    void setScale(jt::Vector2f const& scale) override;
    jt::Vector2f getScale() const override;

    void setOriginInternal(jt::Vector2f const& origin) override;

    void doRotate(float /*rot*/) override;

    void setColorFunction(std::function<jt::Color(jt::Vector2f const&)>);

private:
    mutable std::vector<std::shared_ptr<jt::Sprite>> m_tileSetSprites {};
    std::function<jt::Color(jt::Vector2f const&)> m_colorFunction { nullptr };

    std::vector<TileInfo> m_tiles {};

    jt::Vector2f m_position { 0.0f, 0.0f };
    jt::Vector2f m_scale { 1.0f, 1.0f };
    Color m_color { jt::colors::White };

    jt::Vector2f m_mapSizeInPixel { 0.0f, 0.0f };

    bool isTileVisible(TileInfo const& tile) const;
    void calculateMapSize();
};

} // namespace tilemap
} // namespace jt

#endif // !JAMTEMPLATE_TILEMAP_HPP
