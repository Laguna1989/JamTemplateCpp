
#include "stars.hpp"

jt::Stars::Stars(std::size_t count, jt::Color const& col, jt::Vector2f const& screenSizeHint)
    : m_color { col }
    , m_screenSizeHint { screenSizeHint }
{
    m_stars.resize(count);
}

void jt::Stars::doCreate()
{
    for (auto i = 0u; i != m_stars.size(); ++i) {
        auto star = std::make_unique<Star>();
        star->setGameInstance(getGame());
        star->create();
        star->setColor(m_color);
        star->setPosition(m_screenSizeHint);

        m_stars[i] = std::move(star);
    }
}

void jt::Stars::doUpdate(float const elapsed)
{
    if (!m_enabled) {
        return;
    }
    for (auto& star : m_stars) {
        star->update(elapsed);
    }
}

void jt::Stars::doDraw() const
{
    if (!m_enabled) {
        return;
    }
    for (auto const& star : m_stars) {
        star->draw();
    }
}

void jt::Stars::setEnabled(bool enable) { m_enabled = enable; }

void jt::Stars::setCamMovementFactor(float factor)
{
    for (auto& star : m_stars) {
        star->setCamMovementFactor(factor);
    }
}

void jt::Stars::setZ(int zLayer)
{
    for (auto& star : m_stars) {
        star->setZ(zLayer);
    }
}
