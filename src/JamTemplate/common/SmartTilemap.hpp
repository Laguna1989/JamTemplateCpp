#ifndef GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
#define GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "InfoRect.hpp"
#include "SmartDrawable.hpp"
#include "SmartSprite.hpp"
#include "rendertarget.hpp"
#include "tileson.h"
#include <memory>
#include <vector>

namespace jt {

// forward declaration
class GameBase;

class SmartTilemap : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartTilemap>;

    SmartTilemap(std::string const& path);

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const;

    void doUpdate(float elapsed);

    void setColor(jt::Color const& col);
    const jt::Color getColor() const;

    void setPosition(jt::Vector2 const& pos);
    const jt::Vector2 getPosition() const;

    // sf::Transform const getTransform() const;
    jt::Rect const getGlobalBounds() const;
    jt::Rect const getLocalBounds() const;

    void setFlashColor(jt::Color const& col);
    const jt::Color getFlashColor() const;

    void setScale(jt::Vector2 const& scale);
    const jt::Vector2 getScale() const;

    const jt::Vector2u getMapSizeInTiles();

    void setOrigin(jt::Vector2 const& origin);
    const jt::Vector2 getOrigin() const;

    void doRotate(float /*rot*/);

    void setScreenSizeHint(jt::Vector2 const& hint, std::shared_ptr<GameBase> ptr);

    // FIXME: Not ideal because it only supports rectangles.
    std::map<std::string, std::vector<InfoRect>> getObjectGroups() { return m_objectGroups; };
    void toggleObjectGroupVisibility() { m_highlightObjectGroups = !m_highlightObjectGroups; };

private:
    std::unique_ptr<tson::Map> m_map;
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<InfoRect>> m_objectGroups;
    bool m_highlightObjectGroups = false;
    mutable std::vector<std::shared_ptr<jt::SmartSprite>> m_tileSprites;

    jt::Vector2 m_position;

    jt::Vector2 m_screenSizeHint;
    std::weak_ptr<GameBase> m_gamePtr;
};

} // namespace jt

#endif // !JAMTEMPLATE_TILEMAP_HPP_GUARD
