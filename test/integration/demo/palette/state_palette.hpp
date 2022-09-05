#ifndef JAMTEMPLATE_STATE_PALETTE_HPP
#define JAMTEMPLATE_STATE_PALETTE_HPP

#include <game_state.hpp>
#include <shape.hpp>

class StatePalette : public jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    void createShapesFromGPL();
    void createShapesFromValueGradient();
    void createShapesFromHueGradient();
    void createShapesFromSaturationGradient();
};

#endif // JAMTEMPLATE_STATE_PALETTE_HPP
