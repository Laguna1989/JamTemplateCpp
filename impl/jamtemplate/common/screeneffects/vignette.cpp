#include "vignette.hpp"
#include <game_interface.hpp>
#include <sprite.hpp>

jt::Vignette::Vignette(jt::Vector2f const& size)
    : m_size { size }
{
}

void jt::Vignette::doCreate()
{
    m_vignette = std::make_shared<jt::Sprite>("#v#" + std::to_string(static_cast<int>(m_size.x))
            + "#" + std::to_string(static_cast<int>(m_size.y)),
        textureManager());
    m_vignette->setIgnoreCamMovement(true);
    m_vignette->setColor({ 0, 0, 0, 140 });
}

void jt::Vignette::doUpdate(float const elapsed) { m_vignette->update(elapsed); }

void jt::Vignette::doDraw() const
{
    if (m_enabled) {
        m_vignette->draw(renderTarget());
    }
}

void jt::Vignette::setEnabled(bool enabled) { m_enabled = enabled; }

void jt::Vignette::setColor(jt::Color const& col) { m_vignette->setColor(col); }

void jt::Vignette::setZ(int zLayer) { m_vignette->setZ(zLayer); }
