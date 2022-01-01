#include "animation.hpp"
#include "sprite.hpp"
#include "texture_manager_interface.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace jt {

namespace {

std::shared_ptr<jt::Sprite> getCurrentSprite(
    Animation::AnimationMapType const& frames, std::string const& animName, size_t const animIndex)
{
    auto const cit = frames.find(animName);
    if (cit == frames.cend()) {
        throw std::invalid_argument { "AnimName: '" + animName + "' not part of animation" };
    }

    return cit->second.at(animIndex);
}

} // namespace

void Animation::add(std::string const& fileName, std::string const& animName,
    jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
    float frameTimeInSeconds, TextureManagerInterface& textureManager)
{
    if (frameIndices.empty()) {
        throw std::invalid_argument { "animation frame indices are empty." };
    }
    if (animName.empty()) {
        throw std::invalid_argument { "animation name is empty." };
    }
    if (m_frames.count(animName) != 0) {
        std::cout << "Warning: Overwriting old animation with name: " << animName << std::endl;
    }
    if (frameTimeInSeconds <= 0) {
        throw std::invalid_argument { "animation frame time is negative or zero." };
    }

    m_frames[animName] = std::vector<jt::Sprite::Sptr> {};
    m_time[animName] = frameTimeInSeconds;

    for (auto const idx : frameIndices) {
        jt::Recti const rect { static_cast<int>(idx * imageSize.x), 0,
            static_cast<int>(imageSize.x), static_cast<int>(imageSize.y) };
        Sprite::Sptr sptr = std::make_shared<Sprite>(fileName, rect, textureManager);
        m_frames[animName].push_back(sptr);
    }
}

bool Animation::hasAnimation(std::string const& animationName) const
{
    return (m_frames.count(animationName) != 0);
}

void Animation::play(std::string const& animationName, size_t startFrameIndex, bool restart)
{
    if (m_frames.count(animationName) == 0) {
        throw std::invalid_argument { "anim name not part of animation: " + animationName };
    }

    if (m_currentAnimName != animationName || restart) {
        m_currentIdx = startFrameIndex;
        m_currentAnimName = animationName;
        m_frameTime = 0;
    }
}

void Animation::setColor(jt::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setColor(col);
        }
    }
}

jt::Color Animation::getColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getColor();
}

void Animation::setPosition(jt::Vector2f const& pos) { m_position = pos; }
jt::Vector2f Animation::getPosition() const { return m_position; }

jt::Rectf Animation::getGlobalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getGlobalBounds();
}
jt::Rectf Animation::getLocalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getLocalBounds();
}

void Animation::setFlashColor(jt::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setFlashColor(col);
        }
    }
}
jt::Color Animation::getFlashColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getFlashColor();
}

void Animation::setScale(jt::Vector2f const& scale)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setScale(scale);
        }
    }
}
jt::Vector2f Animation::getScale() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getScale();
}

void Animation::setOrigin(jt::Vector2f const& origin)
{
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setOrigin(origin);
        }
    }
}
jt::Vector2f Animation::getOrigin() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getOrigin();
}

void Animation::setShadowActive(bool active)
{
    DrawableImpl::setShadowActive(active);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowActive(active);
        }
    }
}
void Animation::setShadowColor(jt::Color const& col)
{
    DrawableImpl::setShadowColor(col);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowColor(col);
        }
    }
}
void Animation::setShadowOffset(jt::Vector2f const& v)
{
    DrawableImpl::setShadowOffset(v);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowOffset(v);
        }
    }
}

void Animation::doDrawShadow(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const { }

void Animation::doDraw(std::shared_ptr<jt::RenderTarget> const sptr) const
{
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Drawing Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
}

void Animation::doDrawFlash(std::shared_ptr<jt::RenderTarget> const /*sptr*/) const { }

void Animation::doFlash(float t, jt::Color col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->flash(t, col);
        }
    }
}

void Animation::doUpdate(float elapsed)
{
    // check if valid
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Update Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    // proceed time
    m_frameTime += elapsed;
    while (m_frameTime >= m_time[m_currentAnimName]) {
        m_frameTime -= m_time[m_currentAnimName];
        m_currentIdx++;
        if (m_currentIdx >= m_frames.at(m_currentAnimName).size()) {
            if (m_isLooping) {
                m_currentIdx = 0;
            } else {
                m_currentIdx = m_frames.at(m_currentAnimName).size() - 1;
            }
        }
    }
    // set position
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setPosition(m_position + getShakeOffset() + getOffset());
            spr->update(elapsed);
            spr->setIgnoreCamMovement(DrawableImpl::getIgnoreCamMovement());
        }
    }
}

void Animation::doRotate(float rot)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setRotation(rot);
        }
    }
}
float Animation::getCurrentAnimationSingleFrameTime() const { return m_time.at(m_currentAnimName); }
float Animation::getCurrentAnimTotalTime() const
{
    return getCurrentAnimationSingleFrameTime() * getNumberOfFramesInCurrentAnimation();
}
std::size_t Animation::getNumberOfFramesInCurrentAnimation() const
{
    return m_frames.at(m_currentAnimName).size();
}
std::string Animation::getCurrentAnimationName() const { return m_currentAnimName; }

bool Animation::getIsLooping() const { return m_isLooping; }
void Animation::setLooping(bool isLooping) { m_isLooping = isLooping; }
std::size_t Animation::getCurrentAnimationFrameIndex() const { return m_currentIdx; }

} // namespace jt
