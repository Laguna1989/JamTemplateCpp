#include "Hud.hpp"
#include "Color.hpp"
#include "GameInterface.hpp"

Hud::Hud() = default;

void Hud::AddScoreP1(int i)
{
    m_scoreP1 += i;
    if (m_scoreP1 < 0) {
        m_scoreP1 = 0;
    }
}

void Hud::AddScoreP2(int i)
{
    m_scoreP2 += i;
    if (m_scoreP2 < 0) {
        m_scoreP2 = 0;
    }
}

void Hud::doUpdate(float const elapsed)
{
    if (m_scoreP1 >= 0) {
        m_scoreP1Text->setText("P1 Score: " + std::to_string(m_scoreP1));
    }
    if (m_scoreP2 >= 0) {
        m_scoreP2Text->setText("P2 Score: " + std::to_string(m_scoreP2));
    }

    m_scoreP1Text->update(elapsed);
    m_scoreP2Text->update(elapsed);
}

void Hud::doDraw() const
{
    if (m_scoreP1 >= 0) {
        m_scoreP1Text->draw(getGame()->getRenderTarget());
    }
    if (m_scoreP2 >= 0) {
        m_scoreP2Text->draw(getGame()->getRenderTarget());
    }
}

void Hud::doCreate()
{
    m_scoreP1Text = std::make_shared<jt::Text>();
    m_scoreP1Text->loadFont("assets/font.ttf", 16, getGame()->getRenderTarget());
    m_scoreP1Text->setColor(jt::Color { 248, 249, 254 });
    m_scoreP1Text->update(0.0f);
    m_scoreP1Text->SetTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP1Text->setPosition({ 20, 325 });

    m_scoreP2Text = std::make_shared<jt::Text>();
    m_scoreP2Text->loadFont("assets/font.ttf", 16, getGame()->getRenderTarget());
    m_scoreP2Text->setColor(jt::Color { 248, 249, 254 });
    m_scoreP2Text->update(0.0f);
    m_scoreP2Text->SetTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP2Text->setPosition({ 650 / 2 + 10, 325 });
}
