#ifndef JAMTEMPLATE_GAMEPAD_VISUALIZER_HPP
#define JAMTEMPLATE_GAMEPAD_VISUALIZER_HPP

#include <game_object.hpp>
#include <input/input_manager_interface.hpp>
#include <shape.hpp>
#include <text.hpp>
#include <memory>

class GamepadVisualizer : public jt::GameObject {
public:
    explicit GamepadVisualizer(std::size_t id);
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

private:
    std::size_t m_id { 0 };
    std::shared_ptr<jt::Shape> backgroundLeft;
    std::shared_ptr<jt::Shape> backgroundRight;
    std::shared_ptr<jt::Shape> dotLeft;
    std::shared_ptr<jt::Shape> dotRight;
    std::shared_ptr<jt::Text> text;

    std::string getPressedKey(jt::GamepadButtonCode b);
};

#endif // JAMTEMPLATE_GAMEPAD_VISUALIZER_HPP
