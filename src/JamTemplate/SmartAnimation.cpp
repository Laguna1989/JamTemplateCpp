#include "SmartAnimation.hpp"
#include "SmartSprite.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace JamTemplate {

namespace {

std::shared_ptr<JamTemplate::SmartSprite> getCurrentSprite(
    SmartAnimation::AnimationMapType const& frames, std::string const& animName,
    size_t const animIndex)
{
    auto const cit = frames.find(animName);
    if (cit == frames.cend()) {
        throw std::invalid_argument { "AnimName: '" + animName + "' not part of animation" };
    }

    return cit->second.at(animIndex);
}

} // namespace

void SmartAnimation::add(std::string const& fileName, std::string const& animName,
    sf::Vector2u const& size, std::vector<unsigned int> const& frameIndices, float frameTime)
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

    m_frames[animName] = std::vector<JamTemplate::SmartSprite::Sptr> {};
    m_time[animName] = frameTime;

    for (auto const idx : frameIndices) {
        sf::IntRect const rect { static_cast<int>(idx * size.x), 0, static_cast<int>(size.x),
            static_cast<int>(size.y) };
        SmartSprite::Sptr sptr = std::make_shared<SmartSprite>();
        sptr->loadSprite(fileName, rect);
        m_frames[animName].push_back(sptr);
    }
}

void SmartAnimation::play(std::string const& animName, size_t startFrame, bool restart)
{
    if (m_currentAnimName != animName || restart) {
        m_currentIdx = startFrame;
        m_currentAnimName = animName;
        m_frameTime = 0;
    }
}

void SmartAnimation::setColor(sf::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setColor(col);
        }
    }
}

sf::Color const SmartAnimation::getColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getColor();
}

void SmartAnimation::setPosition(sf::Vector2f const& pos) { m_position = pos; }
sf::Vector2f const SmartAnimation::getPosition() const { return m_position; }

sf::Transform const SmartAnimation::getTransform() const
{
    sf::Transform trans;
    for (auto const& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            trans = sptr->getTransform();
        }
    }
    return trans;
}
sf::FloatRect const SmartAnimation::getGlobalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getGlobalBounds();
}
sf::FloatRect const SmartAnimation::getLocalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getLocalBounds();
}

void SmartAnimation::setFlashColor(sf::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setFlashColor(col);
        }
    }
}
const sf::Color SmartAnimation::getFlashColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getFlashColor();
}

void SmartAnimation::setScale(sf::Vector2f const& scale)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setScale(scale);
        }
    }
}
const sf::Vector2f SmartAnimation::getScale() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getScale();
}

void SmartAnimation::setOrigin(sf::Vector2f const& origin)
{
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setOrigin(origin);
        }
    }
}
sf::Vector2f const SmartAnimation::getOrigin() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getOrigin();
}

void SmartAnimation::setShadowActive(bool active)
{
    SmartObject::setShadowActive(active);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowActive(active);
        }
    }
}
void SmartAnimation::setShadowColor(sf::Color const& col)
{
    SmartObject::setShadowColor(col);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowColor(col);
        }
    }
}
void SmartAnimation::setShadowOffset(sf::Vector2f const& v)
{
    SmartObject::setShadowOffset(v);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowOffset(v);
        }
    }
}

void SmartAnimation::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const { }

void SmartAnimation::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Drawing SmartAnimation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
}

void SmartAnimation::doDrawFlash(std::shared_ptr<sf::RenderTarget> const /*sptr*/) const { }

void SmartAnimation::doFlash(float t, sf::Color col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->flash(t, col);
        }
    }
}

void SmartAnimation::doUpdate(float elapsed)
{
    // check if valid
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Update SmartAnimation with invalid animName: '" + m_currentAnimName
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
            spr->setPosition(m_position + getShakeOffset() + getOffset() + getCamOffset());
            spr->update(elapsed);
        }
    }
}

void SmartAnimation::doRotate(float rot)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setRotation(rot);
        }
    }
}

} // namespace JamTemplate
