#ifndef GAME_PLAYER_GRAPHICS_COMPONENT_HPP
#define GAME_PLAYER_GRAPHICS_COMPONENT_HPP

#include <animation.hpp>
#include <game_interface.hpp>
#include <player/graphics/graphics_component_interface.hpp>
#include <memory>

class GraphicsComponentImpl : public GraphicsComponentInterface {
public:
    explicit GraphicsComponentImpl(std::shared_ptr<jt::GameInterface> gameInterface);

    void updateGraphics(float elapsed) override;
    void setPosition(jt::Vector2f const& playerPosition) override;

    void draw(std::shared_ptr<jt::RenderTargetInterface> target) override;
    void flash(float time, jt::Color const& color) override;
    bool setAnimationIfNotSet(std::string const& newAnimationName) override;
    std::string getCurrentAnimation() const override;

private:
    void createAnimation(jt::TextureManagerInterface& textureManager);
    std::shared_ptr<jt::Animation> m_animation;
};

#endif // GAME_PLAYER_GRAPHICS_COMPONENT_HPP
