#ifndef JAMTEMPLATE_SFML_SETUP_HPP
#define JAMTEMPLATE_SFML_SETUP_HPP

#include <graphics/render_target_interface.hpp>
#include <render_target_layer.hpp>
#include <texture_manager_interface.hpp>
#include <memory>

std::shared_ptr<jt::RenderTargetLayer> getRenderTarget();
std::shared_ptr<jt::RenderTargetInterface> getRenderTargetContainer();
jt::TextureManagerInterface& getTextureManager();

#endif // JAMTEMPLATE_SFML_SETUP_HPP
