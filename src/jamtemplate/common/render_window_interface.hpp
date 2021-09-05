#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_INTERFACE_GUARD_HPP

#include "render_target.hpp"
#include "vector.hpp"
#include <memory>
#include <string>

namespace jt {

class Sprite;

class RenderWindowInterface {
public:
    virtual ~RenderWindowInterface() = default;

    virtual bool isOpen() const = 0;
    virtual void checkForClose() = 0;

    virtual std::shared_ptr<jt::renderTarget> createRenderTarget() = 0;

    virtual jt::Vector2 getSize() const = 0;

    virtual void draw(std::shared_ptr<jt::Sprite>) = 0;

    virtual void display() = 0;

    virtual jt::Vector2 getMousePosition() = 0;
    virtual jt::Vector2 getMousePositionScreen(float zoom) = 0;
    virtual void setMouseCursorVisible(bool visible) = 0;
};
} // namespace jt
#endif
