#ifndef JAMTEMPLATE_STATE_PALETTE_HPP
#define JAMTEMPLATE_STATE_PALETTE_HPP

#include "color/palette.hpp"
#include <game_state.hpp>
#include <shape.hpp>

class StatePalette : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    void createShapesFromGPL();
    void createShapesFromValueGradient();
    void createShapesFromHueGradient();
    void createShapesFromSaturationGradient();
    void createShapesFromSprite();

    void createPaletteShapes(jt::Palette const& palette_saturation, float ypos);
};

#endif // JAMTEMPLATE_STATE_PALETTE_HPP
