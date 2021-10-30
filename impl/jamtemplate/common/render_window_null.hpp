#ifndef MYAWESOMEGAME_RENDER_WINDOW_NULL_HPP
#define MYAWESOMEGAME_RENDER_WINDOW_NULL_HPP

#include "render_window_interface.hpp"

namespace jt {
namespace null_objects {
/// Nullobj pattern for RenderWindow
class RenderWindowNull : public ::jt::RenderWindowInterface {
public:
    RenderWindowNull(unsigned int width, unsigned int height, std::string const& title);
    bool isOpen() const override;
    void checkForClose() override;
    std::shared_ptr<jt::renderTarget> createRenderTarget() override;
    Vector2 getSize() const override;
    void draw(std::unique_ptr<jt::Sprite>& ptr) override;
    void display() override;
    Vector2 getMousePosition() override;
    void setMouseCursorVisible(bool visible) override;
    bool getMouseCursorVisible() const override;

private:
    jt::Vector2 m_size { 0.0f, 0.0f };
    bool m_mouseCursorVisible { true };
};
} // namespace null_objects
} // namespace jt

#endif // MYAWESOMEGAME_RENDER_WINDOW_NULL_HPP
