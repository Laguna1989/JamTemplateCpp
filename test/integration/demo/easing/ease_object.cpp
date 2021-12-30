#include "ease_object.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"

EaseObject::EaseObject(std::string const& name,
    std::function<float(float, float, float, float)> func, jt::Vector2f offset)
{
    m_textString = name;
    m_func = func;
    jt::Vector2f const ofs { 16.0f, 16.0f };

    float const spacingX = 80.0f;
    float const spacingY = 84.0f;
    m_offset = ofs + jt::Vector2f { offset.x * spacingX, offset.y * spacingY };
}

void EaseObject::doCreate()
{
    m_backgroundShape = jt::dh::createShapeRect(
        jt::Vector2f { 64.0f, 64.0f }, jt::colors::Gray, getGame()->gfx().textureManager());
    m_backgroundShape->setPosition(m_offset);
    m_objectShape
        = jt::dh::createShapeCircle(3, jt::colors::Red, getGame()->gfx().textureManager());
    m_text = jt::dh::createText(getGame()->gfx().target(), m_textString, 10);
    m_text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_text->setPosition(m_backgroundShape->getPosition() + jt::Vector2f { 0.0f, 64.0f });
}

void EaseObject::doUpdate(float const elapsed)
{
    m_backgroundShape->update(elapsed);

    auto const max = 1.5f;
    auto v = getAge();
    while (v >= max) {
        v -= max;
    }
    v /= max;

    auto translatedValue = m_func(v, 0.0f, 1.0f, 1.0f);
    jt::Vector2f const pos { m_offset.x + v * 60.0f, m_offset.y + 58.0f - translatedValue * 60.0f };
    m_objectShape->setPosition(pos);
    m_objectShape->update(elapsed);

    m_text->update(elapsed);
}
void EaseObject::doDraw() const
{
    m_backgroundShape->draw(getGame()->gfx().target());
    m_objectShape->draw(getGame()->gfx().target());
    m_text->draw(getGame()->gfx().target());
}
