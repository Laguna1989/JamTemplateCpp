#ifndef GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include "DrawableImpl.hpp"
#include "Rendertarget.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

// forward declaration
class Sprite;

class Animation : public DrawableImpl {
public:
    using Sptr = std::shared_ptr<Animation>;
    using AnimationMapType = std::map<std::string, std::vector<std::shared_ptr<Sprite>>>;

    Animation() = default;

    virtual ~Animation() = default;

    // add a new animation to the pool of available animations
    void add(std::string const& fileName, std::string const& animName, jt::Vector2u const& size,
        std::vector<unsigned int> const& frameIndices, float frameTime);

    // start playing an animation from the pool.
    void play(std::string const& animName, size_t startFrame = 0, bool restart = false);

    void setColor(jt::Color const& col) override;
    const jt::Color getColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    jt::Vector2 const getPosition() const override;

    // sf::Transform const getTransform() const;

    jt::Rect const getGlobalBounds() const override;
    virtual jt::Rect const getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color const getFlashColor() const override;

    virtual void setScale(jt::Vector2 const& scale) override;
    virtual jt::Vector2 const getScale() const override;

    void setOrigin(jt::Vector2 const& origin) override;
    jt::Vector2 const getOrigin() const override;

    void setShadowActive(bool active) override;
    void setShadowColor(jt::Color const& col) override;
    void setShadowOffset(jt::Vector2 const& v) override;

    float getCurrentAnimSingleFrameTime() const;
    float getCurrentAnimTotalTime() const;
    std::size_t getCurrentAnimFrames() const;

private:
    mutable AnimationMapType m_frames;
    std::map<std::string, float> m_time;

    // which animation is playing atm?
    std::string m_currentAnimName = "";
    // which frame of the animation is currently displayed?
    size_t m_currentIdx = 0;

    jt::Vector2 m_position;

    float m_frameTime = 0;

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override;

    void doFlash(float t, jt::Color col = jt::colors::White) override;

    virtual void doUpdate(float elapsed) override;

    void doRotate(float rot) override;
};

} // namespace jt

#endif
