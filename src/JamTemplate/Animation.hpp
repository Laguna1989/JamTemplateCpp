#ifndef JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "SmartSprite.hpp"

namespace JamTemplate {

class Animation : public SmartObject {
public:
    using Sptr = std::shared_ptr<Animation>;

    Animation()
    {
    }

    virtual ~Animation() = default;

    void add(std::string fileName, std::string animName, sf::Vector2u size, std::vector<unsigned int> frameIndices, float frameTime)
    {
        if (frameIndices.size() == 0)
            return;
        m_frames[animName] = std::vector<JamTemplate::SmartSprite::Sptr> {};
        m_time[animName] = frameTime;

        for (const auto idx : frameIndices) {
            sf::IntRect rect { static_cast<int>(idx * size.x), 0, static_cast<int>(size.x), static_cast<int>(size.y) };
            SmartSprite::Sptr sptr = std::make_shared<SmartSprite>();
            sptr->loadSprite(fileName, rect);
            m_frames[animName].push_back(sptr);
        }
    }

    void play(std::string animName, size_t startFrame = 0, bool restart = false)
    {
        if (m_currentAnimName != animName || restart) {
            m_currentIdx = startFrame;
            m_currentAnimName = animName;
            m_frameTime = 0;
        }
    }

    void setColor(sf::Color const& col)
    {
        for (auto& kvp : m_frames) {
            for (auto& spr : kvp.second) {
                spr->setColor(col);
            }
        }
    }

    const sf::Color getColor() const
    {
        sf::Color col;
        for (auto const& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                col = sptr->getColor();
                break;
            }
        }
        return col;
    }

    void setPosition(sf::Vector2f const& pos)
    {
        m_position = pos;
    }
    const sf::Vector2f getPosition() const
    {
        return m_position;
    }

    sf::Transform const getTransform() const
    {
        sf::Transform trans;
        for (auto const& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                trans = sptr->getTransform();
            }
        }
        return trans;
    }
    sf::FloatRect getGlobalBounds() const
    {
        sf::FloatRect rect;
        for (auto const& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                rect = sptr->getGlobalBounds();
                break;
            }
        }
        return rect;
    }
    virtual sf::FloatRect getLocalBounds() const
    {
        sf::FloatRect rect;
        for (auto const& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                rect = sptr->getLocalBounds();
                break;
            }
        }
        return rect;
    }

    void setFlashColor(sf::Color const& col)
    {
        for (auto& kvp : m_frames) {
            for (auto& spr : kvp.second) {
                spr->setFlashColor(col);
            }
        }
    }
    const sf::Color getFlashColor() const
    {
        sf::Color col;
        for (auto const& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                col = sptr->getFlashColor();
                break;
            }
        }
        return col;
    }

    virtual void setScale(sf::Vector2f const& scale)
    {
        for (auto& kvp : m_frames) {
            for (auto& spr : kvp.second) {
                spr->setScale(scale);
            }
        }
    }
    virtual const sf::Vector2f getScale() const
    {
        sf::Vector2f vec;
        for (auto& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                vec = sptr->getScale();
                break;
            }
        }
        return vec;
    }

    void setOrigin(sf::Vector2f const& origin)
    {
        for (auto& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                sptr->setOrigin(origin);
            }
        }
    }
    const sf::Vector2f getOrigin() const
    {
        sf::Vector2f vec;
        for (auto& kvp : m_frames) {
            for (auto const& sptr : kvp.second) {
                vec = sptr->getOrigin();
                break;
            }
        }
        return vec;
    }

private:
    std::map<std::string, std::vector<SmartSprite::Sptr>> m_frames;
    std::map<std::string, float> m_time;

    size_t m_currentIdx = 0;
    std::string m_currentAnimName = "";

    sf::Vector2f m_position;

    float m_frameTime = 0;

    void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const
    {
        if (m_frames.count(m_currentAnimName) == 0)
            return;

        m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
    }

    void doDrawFlash(std::shared_ptr<sf::RenderTarget> /*sptr*/) const
    {
    }

    void doFlash(float t, sf::Color col = sf::Color::White) override
    {
        for (auto& kvp : m_frames) {
            for (auto& spr : kvp.second) {
                spr->flash(t, col);
            }
        }
    }

    virtual void doUpdate(float elapsed)
    {
        // check if valid
        if (m_frames.count(m_currentAnimName) == 0)
            return;

        // proceed time
        m_frameTime += elapsed;
        if (m_frameTime >= m_time[m_currentAnimName]) {
            m_frameTime = 0;
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

    void doRotate(float rot)
    {
        for (auto& kvp : m_frames) {
            for (auto& spr : kvp.second) {
                spr->setRotation(rot);
            }
        }
    }
};

} // namespace JamTemplate

#endif
