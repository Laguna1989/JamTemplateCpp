#include "actor.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"

void Actor::doCreate()
{
    m_sprite = std::make_shared<jt::Sprite>(
        "assets/coin.png", jt::Recti { 0, 0, 16, 16 }, getGame()->gfx().textureManager());
    m_sprite->setOffset(jt::Vector2f { 8, 8 });

    storeActionCommand(getGame()->getActionCommandManager().registerTemporaryCommand(
        "shake", [this](auto /*str*/) { m_sprite->shake(0.5f, 10.0f); }));
}

void Actor::doUpdate(float const elapsed)
{
    m_sprite->update(elapsed);

    walkAlongPath(elapsed);
}

void Actor::walkAlongPath(float const elapsed)
{
    if (m_path.empty()) {
        return;
    }

    float factor = m_walkTimerCurrent / m_walkTimerMax;
    factor = jt::MathHelper::clamp(factor, 0.0f, 1.0f);

    auto const oldTilePos = m_path.begin()->lock()->getTilePosition();
    jt::Vector2f const oldPos = jt::Vector2f { oldTilePos.x * 32.0f, oldTilePos.y * 32.0f };

    auto const nextTileIt = std::next(m_path.begin(), 1);
    auto finalPos = oldPos;
    if (nextTileIt != m_path.end()) {
        auto const nextTilePos = nextTileIt->lock()->getTilePosition();

        auto const newPos = jt::Vector2f { nextTilePos.x * 32.0f, nextTilePos.y * 32.0f };
        jt::Vector2f const diff = newPos - oldPos;
        finalPos += diff * factor;
    }
    m_sprite->setPosition(finalPos);

    m_walkTimerCurrent += elapsed;
    if (m_walkTimerCurrent >= m_walkTimerMax) {
        m_walkTimerCurrent -= m_walkTimerMax;
        m_path.erase(m_path.begin());
    }
}

void Actor::doDraw() const { m_sprite->draw(getGame()->gfx().target()); }

void Actor::setPosition(jt::Vector2u const& posInTiles)
{
    m_sprite->setPosition(jt::Vector2f { posInTiles.x * 32.0f, posInTiles.y * 32.0f });
}
jt::Vector2f Actor::getPosition() const { return m_sprite->getPosition(); }

void Actor::setPath(std::vector<std::shared_ptr<jt::pathfinder::NodeInterface>> const& path)
{
    for (auto& t : path) {
        m_path.push_back(t);
    }

    removeDuplicatesFromPath();
}

void Actor::removeDuplicatesFromPath()
{
    m_path.erase(std::unique(m_path.begin(), m_path.end(),
                     [](auto t1, auto t2) {
                         return t1.lock()->getTilePosition() == t2.lock()->getTilePosition();
                     }),
        m_path.end());
}

jt::Vector2f Actor::getFinalPosition()
{
    if (m_path.empty()) {
        return getPosition();
    } else {
        auto const tpos = m_path.back().lock()->getTilePosition();
        return jt::Vector2f { tpos.x * 32.0f, tpos.y * 32.0f };
    }
}
