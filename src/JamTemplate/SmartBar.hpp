#ifndef JAMTEMPLATE_SMARTBAR_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTBAR_HPP_INCLUDEGUARD

#include "SFML/System/Vector2.hpp"
#include "SmartObject.hpp"
#include <cassert>
#include <memory>
#include <vector>

namespace JamTemplate {

class SmartBar : public JamTemplate::SmartObject {
public:
    using Sptr = std::shared_ptr<SmartBar>;

    SmartBar(float width, float height);

    void setFrontColor(sf::Color const& col);
    void setBackColor(sf::Color const& col);

    void setCurrentValue(float position)
    {
        m_valueCurrent = position;
        if (m_valueCurrent < 0) {
            m_valueCurrent = 0;
        } else if (m_valueCurrent > m_valueMax) {
            m_valueCurrent = m_valueMax;
        }
    }

    void setMaxValue(float max)
    {
        assert(max >= 0);
        m_valueMax = max;
    }

    virtual void setColor(sf::Color const& col) override;
    virtual const sf::Color getColor() const override;

    virtual void setPosition(sf::Vector2f const& pos) override;
    virtual const sf::Vector2f getPosition() const override;

    virtual sf::Transform const getTransform() const override;
    virtual sf::FloatRect const getGlobalBounds() const override;
    virtual sf::FloatRect const getLocalBounds() const override;

    virtual void setFlashColor(sf::Color const& col) override;
    virtual const sf::Color getFlashColor() const override;

    virtual void setScale(sf::Vector2f const& scale) override;
    virtual const sf::Vector2f getScale() const override;

    virtual void setOrigin(sf::Vector2f const& origin) override;
    virtual const sf::Vector2f getOrigin() const override;

private:
    float m_valueMax;
    float m_valueCurrent;

    float const m_width;
    float const m_height;

    mutable sf::RectangleShape m_shapeFull;
    sf::RectangleShape m_shapeProgress;

    virtual void doDraw(std::shared_ptr<sf::RenderTarget> const sptr) const override;
    virtual void doDrawFlash(std::shared_ptr<sf::RenderTarget> const sptr) const override;
    virtual void doDrawShadow(std::shared_ptr<sf::RenderTarget> const sptr) const override;

    // overwrite this method:
    // things to take care of:
    //   - make sure flash object and normal object are at the same position
    virtual void doUpdate(float elapsed) override;
    virtual void doFlash(float /*t*/, sf::Color /*col = sf::Color::White*/);
    virtual void doRotate(float /*rot*/) override;
};

} // namespace JamTemplate

#endif
