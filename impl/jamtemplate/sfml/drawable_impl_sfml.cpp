#include "drawable_impl_sfml.hpp"

void jt::DrawableImplSFML::setCustomShader(
    std::string const& shaderCodeVertex, std::string const& shaderCodeFragment)
{
    m_shader = std::make_shared<sf::Shader>();
    if (shaderCodeVertex == "") {
        m_shader->loadFromMemory(shaderCodeFragment, sf::Shader::Type::Fragment);
    } else if (shaderCodeFragment == "") {
        m_shader->loadFromMemory(shaderCodeVertex, sf::Shader::Type::Vertex);
    } else {
        m_shader->loadFromMemory(shaderCodeVertex, shaderCodeFragment);
    }
}
