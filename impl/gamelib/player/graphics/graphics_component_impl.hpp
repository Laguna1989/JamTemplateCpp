#ifndef GAME_PLAYER_GRAPHICS_COMPONENT_HPP
#define GAME_PLAYER_GRAPHICS_COMPONENT_HPP

#include "animation.hpp"
#include "game_interface.hpp"
#include "graphics_component_interface.hpp"
#include <memory>

class GraphicsComponentImpl : public GraphicsComponentInterface {
public:
    explicit GraphicsComponentImpl(std::shared_ptr<jt::GameInterface> gameInterface);

    void updateGraphics(float elapsed) override;
    void setPosition(jt::Vector2f const& playerPosition) override;

    void draw(std::shared_ptr<jt::RenderTarget> target) override;
    void flash(float time, jt::Color const& color) override;
    bool setAnimationIfNotSet(std::string const& newAnimationName) override;
    void setAnimationLooping(bool isLooping) override;
    std::string getCurrentAnimation() const override;

private:
    void createAnimation(jt::TextureManagerInterface& textureManager);
    std::shared_ptr<jt::Animation> m_animation;
};

#endif // GAME_PLAYER_GRAPHICS_COMPONENT_HPP