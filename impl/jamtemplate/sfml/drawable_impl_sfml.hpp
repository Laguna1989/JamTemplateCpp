#ifndef GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
#define GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP

#include "graphics/drawable_impl.hpp"
#include <SFML/Graphics.hpp>

namespace jt {

class DrawableImplSFML : public jt::DrawableImpl {
public:
    void setCustomShader(
        std::string const& shaderCodeVertex, std::string const& shaderCodeFragment) override;

protected:
    std::shared_ptr<sf::Shader> m_shader { nullptr };
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP