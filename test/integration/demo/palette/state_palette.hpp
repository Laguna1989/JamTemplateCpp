#ifndef JAMTEMPLATE_STATE_PALETTE_HPP
#define JAMTEMPLATE_STATE_PALETTE_HPP

#include <color/palette.hpp>
#include <game_state.hpp>
#include <shape.hpp>
#include <text.hpp>

class StatePalette : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    std::vector<std::shared_ptr<jt::Text>> m_texts;

    void createShapesFromGPL();
    void createShapesFromValueGradient();
    void createShapesFromHueGradient();
    void createShapesFromSaturationGradient();
    void createShapesFromSprite();

    void createPaletteShapes(jt::Palette const& palette, float ypos, std::string const& name);
    void createShapeFromAseprite();
};

#endif // JAMTEMPLATE_STATE_PALETTE_HPP
