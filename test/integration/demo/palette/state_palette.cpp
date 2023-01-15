#include "state_palette.hpp"
#include <color/palette.hpp>
#include <color/palette_builder.hpp>
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <state_select.hpp>
#include <fstream>

void StatePalette::doInternalCreate()
{
    createShapesFromSaturationGradient();
    createShapesFromHueGradient();
    createShapesFromValueGradient();
    createShapesFromGPL();
    createShapesFromSprite();
}
void StatePalette::createShapesFromSprite()
{
    jt::PaletteBuilder builder;
    jt::Sprite sprite { "assets/test/integration/demo/coin.png", jt::Recti { 0, 0, 16, 16 },
        textureManager() };
    auto const palette = builder.addColorsFromPicture(sprite).create();
    createPaletteShapes(palette, 210.0f);
}

void StatePalette::createShapesFromSaturationGradient()
{
    jt::PaletteBuilder builder;
    auto const palette_saturation = builder.addGradientS(90.0f, 0.0f, 100.0f, 80.0f, 5).create();
    createPaletteShapes(palette_saturation, 10.0f);
}

void StatePalette::createShapesFromHueGradient()
{
    jt::PaletteBuilder builder;
    auto const palette_hue = builder.addGradientH(0.0f, 360.0f, 80.0f, 80.0f, 7).create();
    createPaletteShapes(palette_hue, 60.0f);
}

void StatePalette::createShapesFromValueGradient()
{
    jt::PaletteBuilder builder;
    auto palette_value = builder.addGradientV(200.0f, 80.0f, 10.0f, 100.0f, 6).create();
    createPaletteShapes(palette_value, 110.0f);
}

void StatePalette::createShapesFromGPL()
{
    jt::PaletteBuilder builder;
    auto palette_gpl = builder
                           .addColorsFromGPL(R"(GIMP Palette
#Palette Name: Dreamscape8
#Description: A palette made of low saturation colours to give your art a dreamlike quality.
#Colors: 8
201	204	161	c9cca1
202	160	90	caa05a
174	106	71	ae6a47
139	64	73	8b4049
84	51	68	543344
81	82	98	515262
99	120	125	63787d
142	160	145	8ea091
)")
                           .create();
    createPaletteShapes(palette_gpl, 160.0f);
}

void StatePalette::doInternalUpdate(float elapsed)
{
    for (auto s : m_shapes) {
        s->update(elapsed);
    }

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StatePalette::doInternalDraw() const
{
    for (auto s : m_shapes) {
        s->draw(renderTarget());
    }
}

std::string StatePalette::getName() const { return "State Demo Palettes"; }

void StatePalette::createPaletteShapes(jt::Palette const& palette_saturation, float ypos)
{
    for (size_t i = 0; i != palette_saturation.size(); ++i) {
        auto const col = palette_saturation.getColor(i);
        auto s = jt::dh::createShapeRect(jt::Vector2f { 40.0f, 40.0f }, col, textureManager());
        s->setPosition(jt::Vector2f { 10.0f + i * 40.0f, ypos });
        m_shapes.push_back(s);
    }
}
