#include "state_gamepad.hpp"
#include "game_interface.hpp"
#include "shape.hpp"

void StateGamepad::doInternalCreate()
{
    m_backgroundShape = std::make_shared<jt::Shape>();
    m_backgroundShape->makeRect(jt::Vector2f { 50.0f, 50.0f }, getGame()->gfx().textureManager());
    m_backgroundShape->setColor(jt::colors::Gray);

    m_dotShape = std::make_shared<jt::Shape>();
    m_dotShape->makeRect(jt::Vector2f { 3.0f, 3.0f }, getGame()->gfx().textureManager());
    m_dotShape->setOffset(jt::Vector2f { -1.5f, -1.5f });
    m_dotShape->setColor(jt::colors::Red);
}

void StateGamepad::doInternalUpdate(float elapsed)
{
    if (getGame()->input().gamepad(0)->justPressed(jt::GamepadButtonCode::GPA)) {
        m_backgroundShape->flash(0.25f);
    }
    m_backgroundShape->update(elapsed);
    m_dotShape->update(elapsed);
}

void StateGamepad::doInternalDraw() const
{
    for (auto i = 0; i != 3; ++i) {
        m_backgroundShape->setPosition(jt::Vector2f { 25.0f, 25.0f + (10.0f + 50.0f) * i });
        m_backgroundShape->update(0.0f);
        m_backgroundShape->draw(getGame()->gfx().target());

        auto const gp0l = getGame()->input().gamepad(i)->getAxis(jt::GamepadAxisCode::ALeft);
        jt::Vector2f const halfsize { m_backgroundShape->getLocalBounds().width * 0.5f,
            m_backgroundShape->getLocalBounds().height * 0.5f };
        m_dotShape->setPosition(m_backgroundShape->getPosition() + halfsize
            + jt::Vector2f { gp0l.x * halfsize.x, gp0l.y * halfsize.y });
        m_dotShape->update(0.0f);

        m_dotShape->draw(getGame()->gfx().target());

        m_backgroundShape->setPosition(
            jt::Vector2f { 25.0f + 10.0f + 50.0f, 25.0f + (10.0f + 50.0f) * i });
        m_backgroundShape->update(0.0f);
        m_backgroundShape->draw(getGame()->gfx().target());

        auto const gp0r = getGame()->input().gamepad(i)->getAxis(jt::GamepadAxisCode::ARight);
        m_dotShape->setPosition(m_backgroundShape->getPosition() + halfsize
            + jt::Vector2f { gp0r.x * halfsize.x, gp0r.y * halfsize.y });
        m_dotShape->update(0.0f);

        m_dotShape->draw(getGame()->gfx().target());
    }
}
