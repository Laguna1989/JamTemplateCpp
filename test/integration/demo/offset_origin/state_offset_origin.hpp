#ifndef JAMTEMPLATE_STATE_OFFSET_ORIGIN_HPP
#define JAMTEMPLATE_STATE_OFFSET_ORIGIN_HPP

#include <game_state.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <memory>
#include <vector>

class StateOffsetOrigin : public jt::GameState {

public:
    std::string getName() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    std::vector<std::shared_ptr<jt::Sprite>> m_sprites;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;
};

#endif // JAMTEMPLATE_STATE_OFFSET_ORIGIN_HPP
