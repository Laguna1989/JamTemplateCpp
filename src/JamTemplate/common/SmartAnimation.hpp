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
    void add(std::string const& fileName, std::string const& animName, jt::vector2u const& size,
        std::vector<unsigned int> const& frameIndices, float frameTime);

    // start playing an animation from the pool.
    void play(std::string const& animName, size_t startFrame = 0, bool restart = false);

    void setColor(jt::color const& col);
    const jt::color getColor() const;

    void setPosition(jt::vector2 const& pos);
    jt::vector2 const getPosition() const;

    sf::Transform const getTransform() const;

    sf::FloatRect const getGlobalBounds() const;
    virtual sf::FloatRect const getLocalBounds() const;

    void setFlashColor(jt::color const& col) override;
    jt::color const getFlashColor() const;

    virtual void setScale(jt::vector2 const& scale) override;
    virtual jt::vector2 const getScale() const;

    void setOrigin(jt::vector2 const& origin);
    jt::vector2 const getOrigin() const;

    void setShadowActive(bool active) override;
    void setShadowColor(jt::color const& col) override;
    void setShadowOffset(jt::vector2 const& v) override;

private:
    mutable AnimationMapType m_frames;
    std::map<std::string, float> m_time;

    // which animation is playing atm?
    std::string m_currentAnimName = "";
    // which frame of the animation is currently displayed?
    size_t m_currentIdx = 0;

    jt::vector2 m_position;

    float m_frameTime = 0;

    void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const;
    void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const;
    void doDrawFlash(std::shared_ptr<sf::RenderTarget> const /*sptr*/) const;

    void doFlash(float t, jt::color col = jt::colors::White) override;

    virtual void doUpdate(float elapsed);

    void doRotate(float rot);
};

} // namespace JamTemplate

#endif
