#ifndef GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD
#define GUARD_JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "InfoRect.hpp"
#include "SmartDrawable.hpp"
#include "rendertarget.hpp"
#include "tileson.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <vector>

namespace jt {

// forward declaration
class GameBase;

class SmartTilemap : public SmartDrawable {
public:
    using Sptr = std::shared_ptr<SmartTilemap>;

    SmartTilemap(std::filesystem::path const& path);

    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const;

    void doDrawFlash(std::shared_ptr<jt::renderTarget> const sptr) const;
    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const;

    void doUpdate(float elapsed);

    void setColor(jt::color const& col);
    const jt::color getColor() const;

    void setPosition(jt::vector2 const& pos);
    const jt::vector2 getPosition() const;

    // sf::Transform const getTransform() const;
    jt::rect const getGlobalBounds() const;
    jt::rect const getLocalBounds() const;

    void setFlashColor(jt::color const& col);
    const jt::color getFlashColor() const;

    void setScale(jt::vector2 const& scale);
    const jt::vector2 getScale() const;

    const jt::vector2u getMapSizeInTiles();

    void setOrigin(jt::vector2 const& origin);
    const jt::vector2 getOrigin() const;

    void doRotate(float /*rot*/);

    void setScreenSizeHint(jt::vector2 const& hint, std::shared_ptr<GameBase> ptr);

    // FIXME: Not ideal because it only supports rectangles.
    std::map<std::string, std::vector<InfoRect>> getObjectGroups() { return m_objectGroups; };
    void toggleObjectGroupVisibility() { m_highlightObjectGroups = !m_highlightObjectGroups; };

private:
    std::unique_ptr<tson::Map> m_map;
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<InfoRect>> m_objectGroups;
    bool m_highlightObjectGroups = false;
    mutable std::vector<std::unique_ptr<sf::Sprite>> m_tileSprites;

    jt::vector2 m_position;

    jt::vector2 m_screenSizeHint;
    std::weak_ptr<GameBase> m_gamePtr;
};

} // namespace jt

#endif // !JAMTEMPLATE_TILEMAP_HPP_GUARD
