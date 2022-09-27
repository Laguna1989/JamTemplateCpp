#ifndef JAMTEMPLATE_PLAYER_HPP
#define JAMTEMPLATE_PLAYER_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <player/graphics/graphics_component_interface.hpp>
#include <player/input/input_component_interface.hpp>
#include <player/sound/sound_component_interface.hpp>

class StateGame;

class Player : public jt::GameObject {
public:
    Player(std::shared_ptr<jt::Box2DWorldInterface> world, StateGame& state);

private:
    StateGame& m_state;

    std::unique_ptr<InputComponentInterface> m_input { nullptr };
    std::unique_ptr<GraphicsComponentInterface> m_graphics { nullptr };
    std::unique_ptr<SoundComponentInterface> m_sound { nullptr };

    std::unique_ptr<jt::Box2DObject> m_b2Object { nullptr };

    virtual void doCreate();
    virtual void doUpdate(float const elapsed);
    virtual void doDraw() const;
};

#endif // JAMTEMPLATE_PLAYER_HPP
