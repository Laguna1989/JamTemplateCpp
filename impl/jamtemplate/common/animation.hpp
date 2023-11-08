#ifndef JAMTEMPLATE_ANIMATION_HPP
#define JAMTEMPLATE_ANIMATION_HPP

#include <graphics/drawable_impl.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace jt {

// forward declaration
class Sprite;
class TextureManagerInterface;

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
    /// \param frameTimeInSeconds how long is each frame displayed. All frames have the same length
    /// \param textureManager the texture manager to load the individual sprites
    void add(std::string const& fileName, std::string const& animName,
        jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
        float frameTimeInSeconds, TextureManagerInterface& textureManager);

    /// \param fileName path to the image to be used, e.g. "assets/coin.png"
    /// \param animName name of this particular animation in the pool
    /// \param imageSize size of one of the animations images, eg. 16x16
    /// \param frameIndices which frames are part of this animation
    /// \param frameTimesInSeconds how long is each frame displayed. Framescan have different
    /// lengths \param textureManager the texture manager to load the individual sprites
    void add(std::string const& fileName, std::string const& animName,
        jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
        std::vector<float> const& frameTimesInSeconds, TextureManagerInterface& textureManager);

    /// Load animations from json file
    /// \param jsonFileName path to the json file, needs to be next to the image file. e.g.
    /// "assets/Pilz.json"
    /// \param textureManager the texture manager to load the individual sprites
    void loadFromJson(std::string const& jsonFileName, TextureManagerInterface& textureManager);

    /// Load animation from aseprite file
    ///
    /// If there are no animations (tags) defined in the aseprite file, a default animation
    /// with name "idle" will be created, which contains alle frames and has a default frame time of
    /// 0.1s.
    ///
    /// \param asepriteFileName path to the aseprite file \param textureManager the
    /// texture manager to load the individual sprites
    void loadFromAseprite(
        std::string const& asepriteFileName, TextureManagerInterface& textureManager);

    /// Set the fame time for a specific animation.
    /// \param animationName the name of the animation
    /// \param frameTimes the individual frame times. The size needs to match the number of frames
    /// in this animation.
    void setFrameTimes(std::string const& animationName, std::vector<float> const& frameTimes);

    /// Check if a specific animation name is present in the pool
    ///
    /// \param animationName
    /// \return true if an animation with animationName is present, false otherwise
    bool hasAnimation(std::string const& animationName) const;

    /// Get all animation names
    /// \return vector of the animation names
    std::vector<std::string> getAllAvailableAnimationNames() const;

    /// Get a random animation name
    ///
    /// Will raise an exception if no animations have been added.
    ///
    /// \return random animation name
    std::string getRandomAnimationName() const;

    /// Start playing an animation from the pool
    ///
    /// \param animationName name of the animation to play
    /// \param startFrameIndex start the animation with this frame index (0 by default)
    /// \param restart if the animation should to be restarted from the beginning or if it should
    /// continue if already playing
    void play(std::string const& animationName, size_t startFrameIndex = 0, bool restart = false);

    /// Set animation looping
    /// By default an animations is looping (true).
    /// If an animation is not looping, it will remain at the last frame of the animation.
    /// \param isLooping value
    void setLooping(std::string const& animName, bool isLooping);

    /// Set all animations looping
    /// By default an animations is looping (true).
    /// If an animation is not looping, it will remain at the last frame of the animation.
    /// \param isLooping
    void setLoopingAll(bool isLooping);

    /// Get looping value for currently playing animation
    ///
    /// Returns false if no animation is playing
    ///
    /// \return true if animation is looping, false otherwise
    bool getCurrentAnimationIsLooping() const;

    /// Get looping value for a specific animation
    /// Raises an exception if no animation with animName found
    /// \param animName the animation to check
    /// \return
    bool getIsLoopingFor(std::string const& animName) const;

    void setColor(jt::Color const& col) override;
    jt::Color getColor() const override;

    void setPosition(jt::Vector2f const& pos) override;
    jt::Vector2f getPosition() const override;

    jt::Rectf getGlobalBounds() const override;
    virtual jt::Rectf getLocalBounds() const override;

    virtual void setScale(jt::Vector2f const& scale) override;
    virtual jt::Vector2f getScale() const override;

    void setOriginInternal(jt::Vector2f const& origin) override;

    void setShadowActive(bool active) override;
    void setShadow(jt::Color const& color, jt::Vector2f const& offset) override;

    void setOutline(jt::Color const& color, int width) override;

    /// Get the frame time for one single frame in the current animation
    ///
    /// \return time set in add for the currently playing animation
    /// will raise an exception if no valid animation is playing
    float getCurrentAnimationSingleFrameTime() const;

    /// Get the total time of the current animation
    ///
    /// \return time for the complete animation to play
    float getCurrentAnimTotalTime() const;

    /// Get the total time of the animation with name animName
    ///
    /// Raises an exception if animName has not been added
    ///
    /// \param animName the name of the animation
    /// \return time for the complete animation to play
    float getAnimTotalTimeFor(std::string const& animName);

    /// Get the number of frames in this animation
    ///
    /// \return number of frames in this animation
    std::size_t getNumberOfFramesInCurrentAnimation() const;

    /// Get the name of the current animation
    ///
    /// \return name of the currently playing animation
    std::string getCurrentAnimationName() const;

    std::size_t getCurrentAnimationFrameIndex() const;

    /// Set the animation speed
    /// \param factor the animation speed factor. Normal value is 1.0, can be in range from -inf to
    /// inf.
    void setAnimationSpeedFactor(float factor);

    /// Get the animation speed
    /// \return animation speed factor. Normal value is 1.0, can be in range from -inf to inf.
    float getAnimationSpeedFactor() const;

private:
    mutable AnimationMapType m_frames {};
    std::map<std::string, std::vector<float>> m_time {};

    bool m_isValid { false };

    // which animation is playing atm?
    std::string m_currentAnimName { "" };
    // which frame of the animation is currently displayed?
    std::size_t m_currentIdx { 0 };

    jt::Vector2f m_position { 0.0f, 0.0f };

    float m_frameTime { 0.0f };

    std::map<std::string, bool> m_isLooping {};

    float m_animationplaybackSpeed { 1.0f };

    void doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const override;
    void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const override;

    void doFlashImpl(float t, jt::Color col = jt::colors::White) override;

    virtual void doUpdate(float elapsed) override;

    void doRotate(float rot) override;
};

} // namespace jt

#endif
