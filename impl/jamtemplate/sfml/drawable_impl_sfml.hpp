#ifndef JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
#define JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP

#include <graphics/drawable_impl.hpp>
#include <SFML/Graphics.hpp>

namespace jt {

class DrawableImplSFML : public jt::DrawableImpl {
public:
    [[deprecated("Currently only implemented for SFML")]] void setCustomShader(
        std::string const& shaderCodeVertex, std::string const& shaderCodeFragment) override;

protected:
    std::shared_ptr<sf::Shader> m_shader { nullptr };

    sf::BlendMode getSfBlendMode() const;

    jt::Vector2f getCompleteCamOffset() const;
};

} // namespace jt

#endif // JAMTEMPLATE_DRAWABLE_IMPL_SFML_HPP
