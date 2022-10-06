#ifndef JAMTEMPLATE_GRAPHICS_COMPONENT_INTERFACE_HPP
#define JAMTEMPLATE_GRAPHICS_COMPONENT_INTERFACE_HPP

#include <color/color.hpp>
#include <graphics/render_target_interface.hpp>
#include <vector.hpp>
#include <memory>

class GraphicsComponentInterface {
public:
    virtual ~GraphicsComponentInterface() = default;
    virtual void updateGraphics(float elapsed) = 0;
    virtual void setPosition(jt::Vector2f const& position) = 0;
    virtual void draw(std::shared_ptr<jt::RenderTargetInterface> target) = 0;
    virtual void flash(float time, jt::Color const& color) = 0;
    virtual bool setAnimationIfNotSet(std::string const& newAnimationName) = 0;

    virtual std::string getCurrentAnimation() const = 0;
};

#endif // JAMTEMPLATE_GRAPHICS_COMPONENT_INTERFACE_HPP
