#ifndef JAMTEMPLATE_WORLD_CLOCK_HPP
#define JAMTEMPLATE_WORLD_CLOCK_HPP

#include <game_object.hpp>
#include <text.hpp>
class WorldClock : public jt::GameObject {
public:
private:
    std::shared_ptr<jt::Text> m_text;

    std::uint32_t m_day { 0u };
    std::uint8_t m_hour { 8u };
    std::uint8_t m_quarter { 0u };

    // TODO move to GP
    float m_timeToAdvanceInSeconds { 10.0f };

    float m_factor { 1.0f };
    float m_time { 0.0f };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
    void updateTime(float const elapsed);
    void updateText();
};

#endif // JAMTEMPLATE_WORLD_CLOCK_HPP
