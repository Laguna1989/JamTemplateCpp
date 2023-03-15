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
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void onDraw() const override;
};

#endif // JAMTEMPLATE_STATE_OFFSET_ORIGIN_HPP
