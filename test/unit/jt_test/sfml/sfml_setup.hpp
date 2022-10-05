#ifndef JAMTEMPLATE_SFML_SETUP_HPP
#define JAMTEMPLATE_SFML_SETUP_HPP

#include <graphics/render_target_container_interface.hpp>
#include <render_target.hpp>
#include <texture_manager_interface.hpp>
#include <memory>

std::shared_ptr<jt::RenderTarget> getRenderTarget();
std::shared_ptr<jt::RenderTargetContainerInterface> getRenderTargetContainer();
jt::TextureManagerInterface& getTextureManager();

#endif // JAMTEMPLATE_SFML_SETUP_HPP
