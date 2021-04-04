#include "Animation.hpp"
#include "Sprite.hpp"
#include <iostream>
#include <map>
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
    jt::Vector2u const& size, std::vector<unsigned int> const& frameIndices, float frameTime)
{
    if (frameIndices.empty())
        return;
    if (animName.empty()) {
        throw std::invalid_argument { "animation name is empty." };
    }
    if (m_frames.count(animName) != 0) {
        std::cout << "Warning: Overwriting old animation with name: " << animName << std::endl;
    }
    if (frameTime <= 0) {
        throw std::invalid_argument { "animation frame time is negative or zero." };
    }

    m_frames[animName] = std::vector<jt::Sprite::Sptr> {};
    m_time[animName] = frameTime;

    for (auto const idx : frameIndices) {
        jt::Recti const rect { static_cast<int>(idx * size.x()), 0, static_cast<int>(size.x()),
            static_cast<int>(size.y()) };
        Sprite::Sptr sptr = std::make_shared<Sprite>();
        sptr->loadSprite(fileName, rect);
        m_frames[animName].push_back(sptr);
    }
}

void Animation::play(std::string const& animName, size_t startFrame, bool restart)
{
    if (m_currentAnimName != animName || restart) {
        m_currentIdx = startFrame;
        m_currentAnimName = animName;
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

jt::Color const Animation::getColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getColor();
}

void Animation::setPosition(jt::Vector2 const& pos) { m_position = pos; }
jt::Vector2 const Animation::getPosition() const { return m_position; }

// sf::Transform const Animation::getTransform() const
//{
//    sf::Transform trans;
//    for (auto const& kvp : m_frames) {
//        for (auto const& sptr : kvp.second) {
//            trans = sptr->getTransform();
//        }
//    }
//    return trans;
//}

jt::Rect const Animation::getGlobalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getGlobalBounds();
}
jt::Rect const Animation::getLocalBounds() const
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
const jt::Color Animation::getFlashColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getFlashColor();
}

void Animation::setScale(jt::Vector2 const& scale)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setScale(scale);
        }
    }
}
const jt::Vector2 Animation::getScale() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getScale();
}

void Animation::setOrigin(jt::Vector2 const& origin)
{
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setOrigin(origin);
        }
    }
}
jt::Vector2 const Animation::getOrigin() const
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
void Animation::setShadowOffset(jt::Vector2 const& v)
{
    DrawableImpl::setShadowOffset(v);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowOffset(v);
        }
    }
}

void Animation::doDrawShadow(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }

void Animation::doDraw(std::shared_ptr<jt::renderTarget> const sptr) const
{
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Drawing Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
}

void Animation::doDrawFlash(std::shared_ptr<jt::renderTarget> const /*sptr*/) const { }

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
            m_currentIdx = 0;
        }
    }
    // set position
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setPosition(m_position + getShakeOffset() + getOffset());
            spr->update(elapsed);
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
float Animation::getCurrentAnimSingleFrameTime() const { return m_time.at(m_currentAnimName); }
float Animation::getCurrentAnimTotalTime() const
{
    return getCurrentAnimSingleFrameTime() * getCurrentAnimFrames();
}
std::size_t Animation::getCurrentAnimFrames() const
{
    return m_frames.at(m_currentAnimName).size();
}
} // namespace jt
