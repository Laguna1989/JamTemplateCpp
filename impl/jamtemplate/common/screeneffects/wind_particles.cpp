#include "wind_particles.hpp"
#include <random/random.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <stdexcept>

jt::WindParticles::WindParticles(
    jt::Vector2f const& screenSize, std::vector<jt::Color> const& colors)
    : m_screenSize { screenSize }
    , m_colors { colors }
{
    if (m_colors.empty()) {
        throw std::invalid_argument {
            "colors list for WindParticles must contain at least one entry,"
        };
    }
}

void jt::WindParticles::doCreate()
{
    for (auto i = 0u; i != 100u; ++i) {
        auto s = std::make_shared<jt::Shape>();
        s->makeRect({ 8, 2 }, textureManager());
        s->setPosition(jt::Random::getRandomPointIn(m_screenSize));
        s->setScreenSizeHint(m_screenSize);

        auto const index = jt::Random::getInt(0, m_colors.size() - 1);
        s->setColor(m_colors.at(index));

        m_shapes.push_back(s);
        m_factors.push_back(jt::Random::getFloatGauss(1, 0.1f));
    }
}

void jt::WindParticles::doUpdate(float const elapsed)
{
    jt::Vector2f const windSpeed { -150.0f, 0.0f };
    for (auto i = 0u; i != m_shapes.size(); ++i) {
        auto& s = m_shapes.at(i);
        auto p = s->getPosition();
        //        float const f =
        p += windSpeed * elapsed * m_windSpeed * m_factors.at(i);
        s->setPosition(p);
        jt::wrapOnScreen(*s.get());
        s->update(elapsed);
    }
}

void jt::WindParticles::doDraw() const
{
    if (!m_enabled) {
        return;
    }
    for (auto const& s : m_shapes) {
        s->draw(renderTarget());
    }
}

void jt::WindParticles::setEnabled(bool enabled) { m_enabled = enabled; }

void jt::WindParticles::setZ(int zLayer)
{
    for (auto const& s : m_shapes) {
        s->setZ(zLayer);
    }
}
