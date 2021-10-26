#include "render_window_null.hpp"
#include <stdexcept>

jt::null_objects::RenderWindowNull::RenderWindowNull(
    unsigned int width, unsigned int height, std::string const& /*title*/)
    : m_size { static_cast<float>(width), static_cast<float>(height) }
{
}

bool jt::null_objects::RenderWindowNull::isOpen() const { return true; }
void jt::null_objects::RenderWindowNull::checkForClose() { }
std::shared_ptr<jt::renderTarget> jt::null_objects::RenderWindowNull::createRenderTarget()
{
#if USE_SFML
    return std::make_shared<jt::renderTarget>();
#else
    return nullptr;
#endif
}
jt::Vector2 jt::null_objects::RenderWindowNull::getSize() const { return m_size; }
void jt::null_objects::RenderWindowNull::draw(std::unique_ptr<jt::Sprite>& ptr)
{
    if (!ptr) {
        throw std::invalid_argument { "cannot draw nullptr sprite" };
    }
}
void jt::null_objects::RenderWindowNull::display() { }
jt::Vector2 jt::null_objects::RenderWindowNull::getMousePosition()
{
    auto const magic_mouse_position = 20.0f;
    return jt::Vector2 { magic_mouse_position, magic_mouse_position };
}

void jt::null_objects::RenderWindowNull::setMouseCursorVisible(bool visible)
{
    m_mouseCursorVisible = visible;
}
bool jt::null_objects::RenderWindowNull::getMouseCursorVisible() const
{
    return m_mouseCursorVisible;
}
