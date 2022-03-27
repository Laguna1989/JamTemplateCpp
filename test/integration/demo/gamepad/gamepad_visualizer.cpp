#include "gamepad_visualizer.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"

GamepadVisualizer::GamepadVisualizer(std::size_t id)
    : m_id { id }
{
}
void GamepadVisualizer::doCreate()
{
    backgroundLeft = std::make_shared<jt::Shape>();
    backgroundLeft->makeRect(jt::Vector2f { 50.0f, 50.0f }, getGame()->gfx().textureManager());
    backgroundLeft->setColor(jt::colors::Gray);
    backgroundLeft->setPosition(jt::Vector2f { 25.0f, 25.0f + (10.0f + 50.0f) * m_id });

    backgroundRight = std::make_shared<jt::Shape>();
    backgroundRight->makeRect(jt::Vector2f { 50.0f, 50.0f }, getGame()->gfx().textureManager());
    backgroundRight->setColor(jt::colors::Gray);
    backgroundRight->setPosition(
        jt::Vector2f { 25.0f + 50.0f + 10.0f, 25.0f + (10.0f + 50.0f) * m_id });

    dotLeft = std::make_shared<jt::Shape>();
    dotLeft->makeRect(jt::Vector2f { 3.0f, 3.0f }, getGame()->gfx().textureManager());
    dotLeft->setOffset(jt::Vector2f { -1.5f, -1.5f });
    dotLeft->setColor(jt::colors::Red);

    dotRight = std::make_shared<jt::Shape>();
    dotRight->makeRect(jt::Vector2f { 3.0f, 3.0f }, getGame()->gfx().textureManager());
    dotRight->setOffset(jt::Vector2f { -1.5f, -1.5f });
    dotRight->setColor(jt::colors::Red);

    text = jt::dh::createText(getGame()->gfx().target(), "", 16);
    text->setPosition(
        jt::Vector2f { 25.0f + 2.0f * (50.0f + 10.0f), 25.0f + (10.0f + 50.0f) * m_id });
    text->setTextAlign(jt::Text::TextAlign::LEFT);
}

void GamepadVisualizer::doUpdate(float const elapsed)
{
    backgroundLeft->update(elapsed);
    backgroundRight->update(elapsed);

    std::string textstring;
    for (auto b : jt::getAllGamepadButtons()) {
        if (getGame()->input().gamepad(m_id)->pressed(b)) {
            textstring += this->getPressedKey(b) + ", ";
        }
    }
    text->setText(textstring);
    text->update(elapsed);

    jt::Vector2f const halfsize { backgroundLeft->getLocalBounds().width * 0.5f,
        backgroundLeft->getLocalBounds().height * 0.5f };

    auto const gpl = getGame()->input().gamepad(m_id)->getAxis(jt::GamepadAxisCode::ALeft);
    dotLeft->setPosition(backgroundLeft->getPosition() + halfsize
        + jt::Vector2f { gpl.x * halfsize.x, gpl.y * halfsize.y });
    dotLeft->update(elapsed);

    auto const gpr = getGame()->input().gamepad(m_id)->getAxis(jt::GamepadAxisCode::ARight);
    dotRight->setPosition(backgroundRight->getPosition() + halfsize
        + jt::Vector2f { gpr.x * halfsize.x, gpr.y * halfsize.y });
    dotRight->update(elapsed);

    if (getGame()->input().gamepad(m_id)->justPressed(jt::GamepadButtonCode::GPA)) {
        backgroundLeft->flash(0.25f);
    }
    if (getGame()->input().gamepad(m_id)->justPressed(jt::GamepadButtonCode::GPB)) {
        backgroundRight->flash(0.125f);
    }
}

void GamepadVisualizer::doDraw() const
{
    backgroundLeft->draw(getGame()->gfx().target());
    backgroundRight->draw(getGame()->gfx().target());

    dotLeft->draw(getGame()->gfx().target());
    dotRight->draw(getGame()->gfx().target());
    text->draw(getGame()->gfx().target());
}

std::string GamepadVisualizer::getPressedKey(jt::GamepadButtonCode b)
{
    if (b == jt::GamepadButtonCode::GPA) {
        return "A";
    }
    if (b == jt::GamepadButtonCode::GPB) {
        return "B";
    }
    if (b == jt::GamepadButtonCode::GPX) {
        return "X";
    }
    if (b == jt::GamepadButtonCode::GPY) {
        return "Y";
    }
    if (b == jt::GamepadButtonCode::GBRB) {
        return "RB";
    }
    if (b == jt::GamepadButtonCode::GBLB) {
        return "LB";
    }
    if (b == jt::GamepadButtonCode::GBBack) {
        return "Back";
    }
    if (b == jt::GamepadButtonCode::GBStart) {
        return "Start";
    }
    if (b == jt::GamepadButtonCode::GBRightStick) {
        return "Right Stick";
    }
    if (b == jt::GamepadButtonCode::GBLeftStick) {
        return "Left Stick";
    }

    return "???";
}
