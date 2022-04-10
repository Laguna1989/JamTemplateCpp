#ifndef MYAWESOMEGAME_PLAYER_HPP
#define MYAWESOMEGAME_PLAYER_HPP

#include <box2dwrapper/box2d_object.hpp>
#include <player/graphics/graphics_component_interface.hpp>
#include <player/input/input_component_interface.hpp>
#include <player/sound/sound_component_interface.hpp>

class StateGame;

class Player : public jt::Box2DObject {
public:
    Player(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def, StateGame& state);

private:
    StateGame& m_state;

    std::unique_ptr<InputComponentInterface> m_input { nullptr };
    std::unique_ptr<GraphicsComponentInterface> m_graphics { nullptr };
    std::unique_ptr<SoundComponentInterface> m_sound { nullptr };

    virtual void doCreate();
    virtual void doUpdate(float const elapsed);
    virtual void doDraw() const;
};

#endif // MYAWESOMEGAME_PLAYER_HPP
