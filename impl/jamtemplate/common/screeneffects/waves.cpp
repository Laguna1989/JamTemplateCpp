#include "waves.hpp"
#include <math_helper.hpp>
#include <random/random.hpp>
#include <system_helper.hpp>

jt::Waves::Waves(std::string const& filename, jt::Rectf const& size,
    std::vector<jt::Rectf> const& exclude, int count)
    : m_filename { filename }
    , m_size { size }
    , m_exclude { exclude }
    , m_count { count }
{
}

void jt::Waves::doCreate()
{
    for (int i = 0; i != m_count; ++i) {
        auto a = std::make_shared<jt::Animation>();
        a->loadFromAseprite(m_filename, textureManager());
        auto selectedAnimationName = a->getRandomAnimationName();
        a->play(selectedAnimationName);
        a->update(0.0f);
        auto const numerOfFrames = a->getNumberOfFramesInCurrentAnimation();
        a->play(selectedAnimationName, jt::Random::getInt(0, numerOfFrames - 1), true);

        auto const p = jt::Random::getRandomPointIn(m_size);
        bool inExcluded { false };
        for (auto const& r : m_exclude) {
            if (jt::MathHelper::checkIsIn(r, p)
                || jt::MathHelper::checkIsIn(r, p + jt::Vector2f { 16.0f, 16.0f })) {
                inExcluded = true;
                break;
            }
        }
        if (inExcluded) {
            --i;
            continue;
        }

        a->setPosition(p);

        m_animations.push_back(a);
    }
}

void jt::Waves::doUpdate(float const elapsed)
{
    for (auto const& a : m_animations) {
        a->update(elapsed);
    }
}

void jt::Waves::doDraw() const
{
    for (auto const& a : m_animations) {
        a->draw(renderTarget());
    }
}

void jt::Waves::setZ(int zLayer)
{
    for (auto const& a : m_animations) {
        a->setZ(zLayer);
    }
}
