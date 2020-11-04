#ifndef JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include "SmartObject.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace JamTemplate {

// forward declaration
class SmartSprite;

class SmartAnimation : public SmartObject {
public:
    using Sptr = std::shared_ptr<SmartAnimation>;
    using AnimationMapType = std::map<std::string, std::vector<std::shared_ptr<SmartSprite>>>;

    SmartAnimation() = default;

    virtual ~SmartAnimation() = default;

    // add a new animation to the pool of available animations
    void add(std::string const& fileName, std::string const& animName, sf::Vector2u const& size,
        std::vector<unsigned int> const& frameIndices, float frameTime);

    // start playing an animation from the pool.
    void play(std::string const& animName, size_t startFrame = 0, bool restart = false);

    void setColor(sf::Color const& col);
    const sf::Color getColor() const;

    void setPosition(sf::Vector2f const& pos);
    sf::Vector2f const getPosition() const;

    sf::Transform const getTransform() const;

    sf::FloatRect const getGlobalBounds() const;
    virtual sf::FloatRect const getLocalBounds() const;

    void setFlashColor(sf::Color const& col) override;
    sf::Color const getFlashColor() const;

    virtual void setScale(sf::Vector2f const& scale) override;
    virtual sf::Vector2f const getScale() const;

    void setOrigin(sf::Vector2f const& origin);
    sf::Vector2f const getOrigin() const;

    void setShadowActive(bool active) override;
    void setShadowColor(sf::Color const& col) override;
    void setShadowOffset(sf::Vector2f const& v) override;

private:
    mutable AnimationMapType m_frames;
    std::map<std::string, float> m_time;

    // which animation is playing atm?
    std::string m_currentAnimName = "";
    // which frame of the animation is currently displayed?
    size_t m_currentIdx = 0;

    sf::Vector2f m_position;

    float m_frameTime = 0;

    void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const;
    void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const;
    void doDrawFlash(std::shared_ptr<sf::RenderTarget> const /*sptr*/) const;

    void doFlash(float t, sf::Color col = sf::Color::White) override;

    virtual void doUpdate(float elapsed);

    void doRotate(float rot);
};

} // namespace JamTemplate

#endif
