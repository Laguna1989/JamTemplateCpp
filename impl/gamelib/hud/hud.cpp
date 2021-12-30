#include "hud.hpp"
#include "../game_properties.hpp"
#include "color.hpp"
#include "game_interface.hpp"
#include "score_display.hpp"

std::shared_ptr<ObserverInterface<int>> Hud::getObserverScoreP1() const { return m_scoreP1Display; }
std::shared_ptr<ObserverInterface<int>> Hud::getObserverScoreP2() const { return m_scoreP2Display; }

void Hud::doCreate()
{
    m_scoreP1Text = std::make_shared<jt::Text>();
    m_scoreP1Text->loadFont("assets/font.ttf", 16, getGame()->gfx().target());
    m_scoreP1Text->setColor(jt::Color { 248, 249, 254 });
    m_scoreP1Text->update(0.0f);
    m_scoreP1Text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP1Text->setPosition({ 10, 4 });

    m_scoreP1Display = std::make_shared<ScoreDisplay>(m_scoreP1Text, "P1 Score: ");

    m_scoreP2Text = std::make_shared<jt::Text>();
    m_scoreP2Text->loadFont("assets/font.ttf", 16, getGame()->gfx().target());
    m_scoreP2Text->setColor(jt::Color { 248, 249, 254 });
    m_scoreP2Text->update(0.0f);
    m_scoreP2Text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP2Text->setPosition({ 600 / 2 - 10, 4 });

    m_scoreP2Display = std::make_shared<ScoreDisplay>(m_scoreP2Text, "P2 Score: ");
}

void Hud::doUpdate(float const elapsed)
{
    m_scoreP1Text->update(elapsed);
    m_scoreP2Text->update(elapsed);
}

void Hud::doDraw() const
{
    m_scoreP1Text->draw(getGame()->gfx().target());
    m_scoreP2Text->draw(getGame()->gfx().target());
}
