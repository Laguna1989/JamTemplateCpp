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

class Animation : public SmartObject {
public:
    using Sptr = std::shared_ptr<Animation>;
    using AnimationMapType = std::map<std::string, std::vector<std::shared_ptr<SmartSprite>>>;

    Animation() = default;

    virtual ~Animation() = default;

    // add a new animation to the pool of available animations
    void add(std::string const& fileName, std::string const& animName, sf::Vector2u const& size,
        std::vector<unsigned int> const& frameIndices, float frameTime);

    // start playing an animation from the pool.
    void play(std::string animName, size_t startFrame = 0, bool restart = false);

    void setColor(sf::Color const& col);
    const sf::Color getColor() const;

    void setPosition(sf::Vector2f const& pos);
    const sf::Vector2f getPosition() const;

    sf::Transform const getTransform() const;

    sf::FloatRect getGlobalBounds() const;
    virtual sf::FloatRect getLocalBounds() const;

    void setFlashColor(sf::Color const& col);
    const sf::Color getFlashColor() const;

    virtual void setScale(sf::Vector2f const& scale);
    virtual sf::Vector2f const getScale() const;

    void setOrigin(sf::Vector2f const& origin);
    const sf::Vector2f getOrigin() const;

private:
    AnimationMapType m_frames;
    std::map<std::string, float> m_time;

    // which animation is playing atm?
    std::string m_currentAnimName = "";
    // which frame of the animation is currently displayed?
    size_t m_currentIdx = 0;

    sf::Vector2f m_position;

    float m_frameTime = 0;

    void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const;

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> /*sptr*/) const;

    void doFlash(float t, sf::Color col = sf::Color::White) override;

    virtual void doUpdate(float elapsed);

    void doRotate(float rot);
};

} // namespace JamTemplate

#endif
