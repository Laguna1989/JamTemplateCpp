#ifndef GUARD_JAMTEMPLATE_STATE_GRADIENT_HPP
#define GUARD_JAMTEMPLATE_STATE_GRADIENT_HPP

#include "game_state.hpp"
#include "shape.hpp"

class StateGradient : public jt::GameState {
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

#endif // MYAWESOMEGAME_STATE_GRADIENT_HPP
