
#include "Animation.hpp"
#include "SmartSprite.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace JamTemplate {

namespace {

std::shared_ptr<JamTemplate::SmartSprite> getCurrentSprite(
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

void Animation::play(std::string const& animName, size_t startFrame, bool restart)
{
    if (m_currentAnimName != animName || restart) {
        m_currentIdx = startFrame;
        m_currentAnimName = animName;
        m_frameTime = 0;
    }
}

void Animation::setColor(sf::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setColor(col);
        }
    }
}

sf::Color const Animation::getColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getColor();
}

void Animation::setPosition(sf::Vector2f const& pos) { m_position = pos; }
sf::Vector2f const Animation::getPosition() const { return m_position; }

sf::Transform const Animation::getTransform() const
{
    sf::Transform trans;
    for (auto const& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            trans = sptr->getTransform();
        }
    }
    return trans;
}
sf::FloatRect const Animation::getGlobalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getGlobalBounds();
}
sf::FloatRect const Animation::getLocalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getLocalBounds();
}

void Animation::setFlashColor(sf::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setFlashColor(col);
        }
    }
}
const sf::Color Animation::getFlashColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getFlashColor();
}

void Animation::setScale(sf::Vector2f const& scale)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setScale(scale);
        }
    }
}
const sf::Vector2f Animation::getScale() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getScale();
}

void Animation::setOrigin(sf::Vector2f const& origin)
{
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setOrigin(origin);
        }
    }
}
sf::Vector2f const Animation::getOrigin() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getOrigin();
}

void Animation::setShadowActive(bool active)
{
    SmartObject::setShadowActive(active);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowActive(active);
        }
    }
}
void Animation::setShadowColor(sf::Color const& col)
{
    SmartObject::setShadowColor(col);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowColor(col);
        }
    }
}
void Animation::setShadowOffset(sf::Vector2f const& v)
{
    SmartObject::setShadowOffset(v);
    for (auto& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setShadowOffset(v);
        }
    }
}

void Animation::doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const { }

void Animation::doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const
{
    if (m_frames.count(m_currentAnimName) == 0) {
        std::cout << "Warning: Drawing Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
}

void Animation::doDrawFlash(std::shared_ptr<sf::RenderTarget> const /*sptr*/) const { }

void Animation::doFlash(float t, sf::Color col)
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

} // namespace JamTemplate
