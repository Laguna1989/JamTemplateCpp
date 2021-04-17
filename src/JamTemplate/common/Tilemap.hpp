#ifndef GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
#define GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "DrawableImpl.hpp"
#include "InfoRect.hpp"
#include "Rendertarget.hpp"
#include "Sprite.hpp"
#include "tileson.h"
#include <memory>
#include <vector>

namespace jt {

// forward declaration
class GameInterface;

class Tilemap : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Tilemap>;

    Tilemap(std::string const& path);

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const;

    void checkIdBounds(const tson::TileObject& tile) const;

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

    void setScreenSizeHint(jt::Vector2 const& hint, std::shared_ptr<GameInterface> ptr);

    // FIXME: Not ideal because it only supports rectangles.
    std::map<std::string, std::vector<InfoRect>> getObjectGroups() { return m_objectGroups; };
    void toggleObjectGroupVisibility() { m_highlightObjectGroups = !m_highlightObjectGroups; };

private:
    std::unique_ptr<tson::Map> m_map;
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<InfoRect>> m_objectGroups;
    bool m_highlightObjectGroups = false;
    mutable std::vector<jt::Sprite> m_tileSprites;

    jt::Vector2 m_position;

    jt::Vector2 m_screenSizeHint;
    std::weak_ptr<GameInterface> m_gamePtr;
};

} // namespace jt

#endif // !JAMTEMPLATE_TILEMAP_HPP_GUARD
