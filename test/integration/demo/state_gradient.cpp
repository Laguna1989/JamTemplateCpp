#include "state_gradient.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "palette.hpp"
#include "state_select.hpp"

void StateGradient::doInternalCreate()
{

    auto palette_saturation = jt::Palette::createGradientS(40.0f, 0.0f, 100.0f, 80.0f, 5);
    for (std::size_t i = 0; i != palette_saturation.size(); ++i) {
        auto const col = palette_saturation.getColor(i);
        auto s = jt::dh::createShapeRect(jt::Vector2 { 40, 40 }, col);
        s->setPosition(jt::Vector2 { 50.0f + i * 40.0f, 50.0f });
        m_shapes.push_back(s);
    }

    auto palette_hue = jt::Palette::createGradientH(0.0f, 360.0f, 80.0f, 80.0f, 8);
    for (std::size_t i = 0; i != palette_hue.size(); ++i) {
        auto const col = palette_hue.getColor(i);
        auto s = jt::dh::createShapeRect(jt::Vector2 { 40, 40 }, col);
        s->setPosition(jt::Vector2 { 50.0f + i * 40.0f, 100.0f });
        m_shapes.push_back(s);
    }

    auto palette_value = jt::Palette::createGradientV(200.0f, 80.0f, 10.0f, 100.0f, 6);
    for (std::size_t i = 0; i != palette_value.size(); ++i) {
        auto const col = palette_value.getColor(i);
        auto s = jt::dh::createShapeRect(jt::Vector2 { 40, 40 }, col);
        s->setPosition(jt::Vector2 { 50.0f + i * 40.0f, 150.0f });
        m_shapes.push_back(s);
    }
}
void StateGradient::doInternalUpdate(float elapsed)
{
    for (auto s : m_shapes) {
        s->update(elapsed);
    }

    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
}
void StateGradient::doInternalDraw() const
{
    for (auto s : m_shapes) {
        s->draw(getGame()->getRenderTarget());
    }
}
