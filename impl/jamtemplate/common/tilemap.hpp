﻿#ifndef GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
#define GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "drawable_impl.hpp"
#include "info_rect.hpp"
#include "render_target.hpp"
#include "sprite.hpp"
#include "tileson.h"
#include <memory>
#include <vector>

namespace jt {

// forward declaration
class GameInterface;

class Tilemap : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Tilemap>;

    explicit Tilemap(std::string const& path);

    void doDraw(std::shared_ptr<jt::renderTarget> sptr) const override;

    void checkIdBounds(tson::TileObject& tile) const;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> sptr) const override;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> sptr) const override;

    void doUpdate(float elapsed) override;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    jt::Vector2 getPosition() const override;

    // sf::Transform const getTransform() const;
    jt::Rect getGlobalBounds() const override;
    jt::Rect getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    void setScale(jt::Vector2 const& scale) override;
    jt::Vector2 getScale() const override;

    jt::Vector2u getMapSizeInTiles();

    void setOrigin(jt::Vector2 const& origin);
    jt::Vector2 getOrigin() const;

    void doRotate(float /*rot*/);

    void setScreenSizeHint(jt::Vector2 const& hint);

    // FIXME: Not ideal because it only supports rectangles.
    std::map<std::string, std::vector<InfoRect>> getObjectGroups() { return m_objectGroups; };
    void toggleObjectGroupVisibility() { m_highlightObjectGroups = !m_highlightObjectGroups; };

private:
    std::unique_ptr<tson::Map> m_map { nullptr };
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<InfoRect>> m_objectGroups {};
    bool m_highlightObjectGroups { false };
    mutable std::vector<jt::Sprite> m_tileSprites {};

    Vector2 m_position { 0.0f, 0.0f };
    Vector2 m_origin { 0.0f, 0.0f };
    Vector2 m_screenSizeHint { 0.0f, 0.0f };
    Vector2 m_scale { 1.0f, 1.0f };
    Color m_color { jt::colors::White };
    Color m_flashColor { jt::colors::White };
};

} // namespace jt

#endif // !JAMTEMPLATE_TILEMAP_HPP_GUARD