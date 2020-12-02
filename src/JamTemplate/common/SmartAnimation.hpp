#ifndef GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include "SmartDrawable.hpp"
#include "rendertarget.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

// forward declaration
class SmartSprite;

class SmartAnimation : public SmartDrawable {
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

    void setColor(jt::color const& col) override;
    const jt::color getColor() const override;

    void setPosition(jt::vector2 const& pos) override;
    jt::vector2 const getPosition() const override;

    // sf::Transform const getTransform() const;

    jt::rect const getGlobalBounds() const override;
    virtual jt::rect const getLocalBounds() const override;

    void setFlashColor(jt::color const& col) override;
    jt::color const getFlashColor() const override;

    virtual void setScale(jt::vector2 const& scale) override;
    virtual jt::vector2 const getScale() const override;

    void setOrigin(jt::vector2 const& origin) override;
    jt::vector2 const getOrigin() const override;

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

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override;

    void doFlash(float t, jt::color col = jt::colors::White) override;

    virtual void doUpdate(float elapsed) override;

    void doRotate(float rot) override;
};

} // namespace jt

#endif
