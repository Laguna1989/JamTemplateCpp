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
sf::BlendMode jt::DrawableImplSFML::getSfBlendMode() const
{
    if (getBlendMode() == jt::BlendMode::ADD) {
        return sf::BlendAdd;
    } else if (getBlendMode() == jt::BlendMode::MUL) {
        return sf::BlendMultiply;
    } else if (getBlendMode() == jt::BlendMode::ALPHA) {
        return sf::BlendAlpha;
    } else {
        throw std::logic_error { "invalid Blend Mode" };
    }
}

jt::Vector2f jt::DrawableImplSFML::getCompleteCamOffset() const
{
    if (getIgnoreCamMovement()) {
        return getCamOffset() + m_camMovementFactor * getStaticCamOffset();
    } else {
        return getCamOffset();
    }
}
