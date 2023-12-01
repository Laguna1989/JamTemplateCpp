#ifndef JAMTEMPLATE_RENDER_WINDOW_NULL_HPP
#define JAMTEMPLATE_RENDER_WINDOW_NULL_HPP

#include <graphics/render_window_interface.hpp>

namespace jt {
namespace null_objects {
/// Nullobj pattern for RenderWindow
class RenderWindowNull : public ::jt::RenderWindowInterface {
public:
    RenderWindowNull(unsigned int width, unsigned int height, std::string const& title);

    void updateGui(float elapsed) override;
    void startRenderGui() override;

    bool isOpen() const override;
    void checkForClose() override;
    std::shared_ptr<jt::RenderTargetLayer> createRenderTarget() override;
    jt::Vector2f getSize() const noexcept override;
    void draw(std::unique_ptr<jt::Sprite>& ptr) override;
    void display() override;
    jt::Vector2f getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const override;
    bool shouldProcessKeyboard() override;
    bool shouldProcessMouse() override;

private:
    jt::Vector2f m_size { 0.0f, 0.0f };
    bool m_mouseCursorVisible { true };
};
} // namespace null_objects
} // namespace jt

#endif // JAMTEMPLATE_RENDER_WINDOW_NULL_HPP
