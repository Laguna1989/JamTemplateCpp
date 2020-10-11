#ifndef JAMTEMPLATE_PLAYBAR_HPP_INCLUDEGUARD
#define JAMTEMPLATE_PLAYBAR_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include "SFML/System/Vector2.hpp"
#include <cassert>
#include <memory>
#include <vector>

namespace JamTemplate {

class PlayBar : public JamTemplate::GameObject {
public:
    using Sptr = std::shared_ptr<PlayBar>;

    virtual void doUpdate(float const /*elapsed*/) override;
    virtual void doDraw() const override;
    virtual void doCreate() override;

    PlayBar(float width, float height);

    void setPosition(sf::Vector2f const& pos);

    void setFrontColor(sf::Color const& col);
    void setBackColor(sf::Color const& col);

    void setCurrentValue(float position)
    {
        m_current_value = position;
        if (m_current_value < 0) {
            m_current_value = 0;
        } else if (m_current_value > m_max_value) {
            m_current_value = m_max_value;
        }
    }

    void setMaxValue(float max)
    {
        assert(max >= 0);
        m_max_value = max;
    }

private:
    float m_max_value;
    float m_current_value;

    float const m_width;
    float const m_height;

    sf::RectangleShape m_shape_full;
    sf::RectangleShape m_shape_progress;
};

}

#endif
