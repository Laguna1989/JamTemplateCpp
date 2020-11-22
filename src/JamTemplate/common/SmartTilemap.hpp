#ifndef JAMTEMPLATE_TILEMAP_HPP_GUARD
#define JAMTEMPLATE_TILEMAP_HPP_GUARD

#include "Rect.hpp"
#include "SmartObject.hpp"
#include "tileson.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <vector>

namespace JamTemplate {

// forward declaration
class Game;

class SmartTilemap : public SmartObject {
public:
    using Sptr = std::shared_ptr<SmartTilemap>;

    SmartTilemap(std::filesystem::path const& path);

    void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const;

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const;
    void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const;

    void doUpdate(float elapsed);

    void setColor(sf::Color const& col);
    const sf::Color getColor() const;

    void setPosition(jt::vector2 const& pos);
    const jt::vector2 getPosition() const;

    sf::Transform const getTransform() const;
    sf::FloatRect const getGlobalBounds() const;
    sf::FloatRect const getLocalBounds() const;

    void setFlashColor(sf::Color const& col);
    const sf::Color getFlashColor() const;

    void setScale(jt::vector2 const& scale);
    const jt::vector2 getScale() const;

    const sf::Vector2i getMapSizeInTiles();

    void setOrigin(jt::vector2 const& origin);
    const jt::vector2 getOrigin() const;

    void doRotate(float /*rot*/);

    void setScreenSizeHint(jt::vector2 const& hint, std::shared_ptr<Game> ptr);

    // FIXME: Not ideal because it only supports rectangles.
    std::map<std::string, std::vector<Rect>> getObjectGroups() { return m_objectGroups; };
    void toggleObjectGroupVisibility() { m_highlightObjectGroups = !m_highlightObjectGroups; };

private:
    std::unique_ptr<tson::Map> m_map;
    // Map from object layer name to vector of objects, all rectangular.
    std::map<std::string, std::vector<Rect>> m_objectGroups;
    bool m_highlightObjectGroups = false;
    mutable std::vector<std::unique_ptr<sf::Sprite>> m_tileSprites;

    jt::vector2 m_position;

    jt::vector2 m_screenSizeHint;
    std::weak_ptr<Game> m_gamePtr;
};

} // namespace JamTemplate

#endif // !JAMTEMPLATE_TILEMAP_HPP_GUARD
