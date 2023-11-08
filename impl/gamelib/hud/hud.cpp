#include "hud.hpp"
#include <color/color.hpp>
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/score_display.hpp>

std::shared_ptr<ObserverInterface<int>> Hud::getObserverScoreP1() const { return m_scoreP1Display; }

std::shared_ptr<ObserverInterface<int>> Hud::getObserverScoreP2() const { return m_scoreP2Display; }

void Hud::doCreate()
{
    m_scoreP1Text = std::make_shared<jt::Text>();
    m_scoreP1Text = jt::dh::createText(renderTarget(), "", 16, jt::Color { 248, 249, 254 });
    m_scoreP1Text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP1Text->setIgnoreCamMovement(true);
    m_scoreP1Text->setPosition({ 10, 4 });

    m_scoreP1Display = std::make_shared<ScoreDisplay>(m_scoreP1Text, "P1 Score: ");

    m_scoreP2Text = jt::dh::createText(renderTarget(), "", 16, jt::Color { 248, 249, 254 });
    m_scoreP2Text->setTextAlign(jt::Text::TextAlign::RIGHT);
    m_scoreP2Text->setIgnoreCamMovement(true);
    m_scoreP2Text->setPosition({ GP::GetScreenSize().x - 10, 4 });

    m_scoreP2Display = std::make_shared<ScoreDisplay>(m_scoreP2Text, "P2 Score: ");
}

void Hud::doUpdate(float const elapsed)
{
    m_scoreP1Text->update(elapsed);
    m_scoreP2Text->update(elapsed);
}

void Hud::doDraw() const
{
    m_scoreP1Text->draw(renderTarget());
    m_scoreP2Text->draw(renderTarget());
}
