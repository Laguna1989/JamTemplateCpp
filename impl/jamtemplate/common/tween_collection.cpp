#include "tween_collection.hpp"
#include <algorithm>

void jt::TweenCollection::add(std::shared_ptr<jt::TweenInterface> tween)
{
    m_tweensToAdd.emplace_back(std::move(tween));
}

void jt::TweenCollection::clear() noexcept
{
    m_tweens.clear();
    m_tweensToAdd.clear();
}

void jt::TweenCollection::update(float const elapsed)
{
    m_tweens.insert(m_tweens.end(), std::move_iterator(m_tweensToAdd.begin()),
        std::move_iterator(m_tweensToAdd.end()));
    m_tweensToAdd.clear();

    if (m_tweens.empty()) {
        return;
    }
    std::erase_if(
        m_tweens, [](std::shared_ptr<TweenInterface> const& tween) { return !(tween->isAlive()); });

    for (auto const& tw : m_tweens) {
        tw->update(elapsed);
    };
}

std::size_t jt::TweenCollection::size() const noexcept { return m_tweens.size() + m_tweensToAdd.size(); }
