#include "scanlines.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <shape.hpp>

jt::ScanLines::ScanLines(jt::Vector2f const& shapeSize, std::size_t shapeCount)
    : m_shapeSize { shapeSize }
    , m_shapeCount { shapeCount }
{
}

void jt::ScanLines::doCreate()
{
    m_shape = jt::dh::createShapeRect(m_shapeSize, jt::Color { 0, 0, 0, 40 }, textureManager());
    m_shape->setIgnoreCamMovement(true);
}

void jt::ScanLines::doDraw() const
{
    if (m_enabled) {
        for (auto i = 0u; i != m_shapeCount; ++i) {
            m_shape->setPosition(jt::Vector2f { 0.0f, i * 2 * m_shapeSize.y });
            m_shape->update(0.1f);
            m_shape->draw(renderTarget());
        }
    }
}

void jt::ScanLines::setEnabled(bool enable) { m_enabled = enable; }

void jt::ScanLines::setColor(jt::Color const& col) { m_shape->setColor(col); }

void jt::ScanLines::setZ(int zLayer) { m_shape->setZ(zLayer); }
