#ifndef JAMTEMPLATE_PLAYBAR_HPP_INCLUDEGUARD
#define JAMTEMPLATE_PLAYBAR_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include <memory>
#include <vector>

namespace JamTemplate {

class PlayBar : public JamTemplate::GameObject {
public:
    using Sptr = std::shared_ptr<PlayBar>;

    virtual void doUpdate(float const /*elapsed*/) override;
    virtual void doDraw() const override;
    virtual void doCreate() override;

    PlayBar(std::int32_t duration, std::int32_t loop_start = 0, std::int32_t loop_end = 0, std::int32_t skip_to = 0);

    void setPosition(std::int32_t position)
    {
        m_position = position;
    }
    void set_y_pos(float y);

private:
    std::int32_t m_duration;
    std::int32_t m_skip;
    std::vector<std::int32_t> m_skip_from;
    std::int32_t m_position;
    std::int32_t m_loop_start;
    std::int32_t m_loop_end;

    float const m_width;

    sf::RectangleShape m_shape_full;
    sf::RectangleShape m_shape_progress;
    sf::RectangleShape m_shape_loop_start;
    sf::RectangleShape m_shape_loop_end;
    sf::RectangleShape m_shape_skip;
    mutable sf::RectangleShape m_shape_skip_from;
};

}

#endif
