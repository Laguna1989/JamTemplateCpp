#include "gamepad_visualizer.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <map>

GamepadVisualizer::GamepadVisualizer(std::size_t id)
    : m_id { id }
{
}
void GamepadVisualizer::doCreate()
{
    backgroundLeft = std::make_shared<jt::Shape>();
    backgroundLeft->makeRect(jt::Vector2f { 50.0f, 50.0f }, textureManager());
    backgroundLeft->setColor(jt::colors::Gray);
    backgroundLeft->setPosition(jt::Vector2f { 25.0f, 25.0f + (10.0f + 50.0f) * m_id });

    backgroundRight = std::make_shared<jt::Shape>();
    backgroundRight->makeRect(jt::Vector2f { 50.0f, 50.0f }, textureManager());
    backgroundRight->setColor(jt::colors::Gray);
    backgroundRight->setPosition(
        jt::Vector2f { 25.0f + 50.0f + 10.0f, 25.0f + (10.0f + 50.0f) * m_id });

    dotLeft = std::make_shared<jt::Shape>();
    dotLeft->makeRect(jt::Vector2f { 3.0f, 3.0f }, textureManager());
    dotLeft->setOffset(jt::Vector2f { -1.5f, -1.5f });
    dotLeft->setColor(jt::colors::Red);

    dotRight = std::make_shared<jt::Shape>();
    dotRight->makeRect(jt::Vector2f { 3.0f, 3.0f }, textureManager());
    dotRight->setOffset(jt::Vector2f { -1.5f, -1.5f });
    dotRight->setColor(jt::colors::Red);

    text = jt::dh::createText(renderTarget(), "", 16);
    text->setPosition(
        jt::Vector2f { 25.0f + 2.0f * (50.0f + 10.0f), 25.0f + (10.0f + 50.0f) * m_id });
    text->setTextAlign(jt::Text::TextAlign::LEFT);
}

void GamepadVisualizer::doUpdate(float const elapsed)
{
    backgroundLeft->update(elapsed);
    backgroundRight->update(elapsed);

    std::string textstring = " ";
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

    if (getGame()->input().gamepad(m_id)->justPressed(jt::GamepadButtonCode::GBA)) {
        backgroundLeft->flash(0.25f);
    }
    if (getGame()->input().gamepad(m_id)->justPressed(jt::GamepadButtonCode::GBB)) {
        backgroundRight->flash(0.125f);
    }
}

void GamepadVisualizer::doDraw() const
{
    backgroundLeft->draw(renderTarget());
    backgroundRight->draw(renderTarget());

    dotLeft->draw(renderTarget());
    dotRight->draw(renderTarget());
    text->draw(renderTarget());
}

std::string GamepadVisualizer::getPressedKey(jt::GamepadButtonCode b)
{
    std::map<jt::GamepadButtonCode, std::string> lookup { { jt::GamepadButtonCode::GBA, "A" },
        { jt::GamepadButtonCode::GBB, "B" }, { jt::GamepadButtonCode::GBX, "X" },
        { jt::GamepadButtonCode::GBY, "Y" }, { jt::GamepadButtonCode::GBLB, "LB" },
        { jt::GamepadButtonCode::GBRB, "RB" }, { jt::GamepadButtonCode::GBBack, "Back" },
        { jt::GamepadButtonCode::GBStart, "Start" },
        { jt::GamepadButtonCode::GBLeftStick, "Left Stick" },
        { jt::GamepadButtonCode::GBRightStick, "Right Stick" },
        { jt::GamepadButtonCode::GBU1, "GBU1" }, { jt::GamepadButtonCode::GBU2, "D-Up" },
        { jt::GamepadButtonCode::GBU3, "D-Down" }, { jt::GamepadButtonCode::GBU4, "D-Left" },
        { jt::GamepadButtonCode::GBU5, "D-Right" }, { jt::GamepadButtonCode::GBU6, "GBU6" },
        { jt::GamepadButtonCode::GBU7, "GBU7" }, { jt::GamepadButtonCode::GBU8, "GBU8" } };
    return lookup[b];

    return "???";
}
