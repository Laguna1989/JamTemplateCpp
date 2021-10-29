#ifndef GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include "drawable_impl.hpp"
#include "render_target.hpp"
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

    /// Add a new animation to the pool of available animations
    ///
    /// \param fileName path to the image to be used, e.g. "assets/coin.png"
    /// \param animName name of this particular animation in the pool
    /// \param imageSize size of one of the animations images, eg. 16x16
    /// \param frameIndices which frames are part of this animation
    /// \param frameTimeInSeconds how long is each frame displayed
    void add(std::string const& fileName, std::string const& animName,
        jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
        float frameTimeInSeconds);

    /// Check if a specific animation name is present in the pool
    ///
    /// \param animationName
    /// \return true if an animation with animationName is present, false otherwise
    bool hasAnimation(std::string const& animationName) const;

    /// Start playing an animation from the pool
    ///
    /// \param animationName name of the animation to play
    /// \param startFrameIndex start the animation with this frame index (0 by default)
    /// \param restart if the animation should to be restarted from the beginning or if it should
    /// continue if already playing
    void play(std::string const& animationName, size_t startFrameIndex = 0, bool restart = false);

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2 const& pos) override;
    jt::Vector2 getPosition() const override;

    jt::Rect getGlobalBounds() const override;
    virtual jt::Rect getLocalBounds() const override;

    void setFlashColor(jt::Color const& col) override;
    jt::Color getFlashColor() const override;

    virtual void setScale(jt::Vector2 const& scale) override;
    virtual jt::Vector2 getScale() const override;

    void setOrigin(jt::Vector2 const& origin) override;
    jt::Vector2 getOrigin() const override;

    void setShadowActive(bool active) override;
    void setShadowColor(jt::Color const& col) override;
    void setShadowOffset(jt::Vector2 const& v) override;

    /// Get the frame time for one single frame in the current animation
    ///
    /// \return the time set in add for the currently playing animation
    /// will raise an exception if no valid animation is playing
    float getCurrentAnimationSingleFrameTime() const;

    /// Get the total time of the current animation
    ///
    /// \return the time for the complete animation to play
    float getCurrentAnimTotalTime() const;

    /// Get the number of frames in this animation
    ///
    /// \return the number of frames in this animation
    std::size_t getNumberOfFramesInCurrentAnimation() const;

    /// Get the name of the current animation
    ///
    /// \return the name of the currently playing animation
    std::string getCurrentAnimationName() const;

private:
    mutable AnimationMapType m_frames {};
    std::map<std::string, float> m_time {};

    // which animation is playing atm?
    std::string m_currentAnimName { "" };
    // which frame of the animation is currently displayed?
    size_t m_currentIdx { 0 };

    jt::Vector2 m_position { 0.0f, 0.0f };

    float m_frameTime { 0.0f };

    void doDrawShadow(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDraw(std::shared_ptr<jt::renderTarget> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const override;

    void doFlash(float t, jt::Color col = jt::colors::White) override;

    virtual void doUpdate(float elapsed) override;

    void doRotate(float rot) override;
};

} // namespace jt

#endif
