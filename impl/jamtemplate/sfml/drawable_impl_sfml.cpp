#include "drawable_impl_sfml.hpp"

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
