#include "state_gradient.hpp"
#include "../state_select.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "palette.hpp"
#include <fstream>
#include <sstream>

void StateGradient::doInternalCreate()
{
    createShapesFromSaturationGradient();
    createShapesFromHueGradient();
    createShapesFromValueGradient();
    createShapesFromGPL();
}

void StateGradient::createShapesFromSaturationGradient()
{
    auto palette_saturation = jt::Palette::createGradientS(40.0f, 0.0f, 100.0f, 80.0f, 5);
    for (size_t i = 0; i != palette_saturation.size(); ++i) {
        auto const col = palette_saturation.getColor(i);
        auto s = jt::dh::createShapeRect(
            jt::Vector2f { 40, 40 }, col, getGame()->gfx().textureManager());
        s->setPosition(jt::Vector2f { 10.0f + i * 40.0f, 10.0f });
        m_shapes.push_back(s);
    }
}

void StateGradient::createShapesFromHueGradient()
{
    auto palette_hue = jt::Palette::createGradientH(0.0f, 360.0f, 80.0f, 80.0f, 7);
    for (size_t i = 0; i != palette_hue.size(); ++i) {
        auto const col = palette_hue.getColor(i);
        auto s = jt::dh::createShapeRect(
            jt::Vector2f { 40, 40 }, col, getGame()->gfx().textureManager());
        s->setPosition(jt::Vector2f { 10.0f + i * 40.0f, 60.0f });
        m_shapes.push_back(s);
    }
}

void StateGradient::createShapesFromValueGradient()
{
    auto palette_value = jt::Palette::createGradientV(200.0f, 80.0f, 10.0f, 100.0f, 6);
    for (size_t i = 0; i != palette_value.size(); ++i) {
        auto const col = palette_value.getColor(i);
        auto s = jt::dh::createShapeRect(
            jt::Vector2f { 40, 40 }, col, getGame()->gfx().textureManager());
        s->setPosition(jt::Vector2f { 10.0f + i * 40.0f, 110.0f });
        m_shapes.push_back(s);
    }
}

void StateGradient::createShapesFromGPL()
{
    std::ifstream file { "assets/crayon-paint.gpl" };
    std::stringstream buffer;
    buffer << file.rdbuf();
    auto palette_gpl = jt::Palette::parseGPL(buffer.str());
    for (size_t i = 0; i != palette_gpl.size(); ++i) {
        auto const col = palette_gpl.getColor(i);
        auto s = jt::dh::createShapeRect(
            jt::Vector2f { 40, 40 }, col, getGame()->gfx().textureManager());
        s->setPosition(jt::Vector2f { 10.0f + i * 40.0f, 160.0f });
        m_shapes.push_back(s);
    }
}

void StateGradient::doInternalUpdate(float elapsed)
{
    for (auto s : m_shapes) {
        s->update(elapsed);
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateGradient::doInternalDraw() const
{
    for (auto s : m_shapes) {
        s->draw(getGame()->gfx().target());
    }
}
std::string StateGradient::getName() const { return "Palettes"; }
