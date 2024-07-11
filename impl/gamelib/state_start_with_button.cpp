#include "state_start_with_button.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <state_intro.hpp>
#include <text.hpp>

void StateStartWithButton::onCreate()
{
    auto const buttonSize = jt::Vector2u { 128, 48 };
    m_button = std::make_shared<jt::Button>(buttonSize, textureManager());
    m_button->addCallback(
        [this]() { getGame()->stateManager().switchState(std::make_shared<StateIntro>()); });
    auto text = jt::dh::createText(renderTarget(), "Start", 24);
    text->setTextAlign(jt::Text::TextAlign::LEFT);
    text->setOrigin({ -34, -6 });
    m_button->setDrawable(text);
    m_button->setPosition(
        GP::GetScreenSize() * 0.5f - jt::Vector2f { buttonSize.x / 2.0f, buttonSize.y / 2.0f });
    add(m_button);
}

void StateStartWithButton::onEnter() { }

void StateStartWithButton::onUpdate(float /*elapsed*/) { }

void StateStartWithButton::onDraw() const { }
