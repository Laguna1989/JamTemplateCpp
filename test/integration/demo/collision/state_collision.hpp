#ifndef DEMO_STATE_COLLISION_HPP
#define DEMO_STATE_COLLISION_HPP

#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_state.hpp>
#include <state_select.hpp>
#include <text.hpp>
#include <memory>
#include <string>

/// Demo state that hosts a single collision scene, e.g. StateCollision<SceneCircleTest>.
/// \tparam Scene a jt::GameObject that implements the scene
template <typename Scene>
class StateCollision : public jt::GameState {
public:
    std::string getName() const override { return "Collision: " + m_scene->getName(); }

private:
    std::shared_ptr<Scene> m_scene { std::make_shared<Scene>() };
    std::shared_ptr<jt::Text> m_title { nullptr };

    void onCreate() override
    {
        m_scene->setGameInstance(getGame());
        m_scene->create();

        m_title = jt::dh::createText(renderTarget(), m_scene->getName(), 12);
        m_title->setTextAlign(jt::Text::TextAlign::LEFT);
        m_title->setPosition(jt::Vector2f { 4.0f, 2.0f });
        m_title->setShadow(jt::colors::Black, jt::Vector2f { 1.0f, 1.0f });

        setAutoDraw(false);
    }

    void onEnter() override { }

    void onUpdate(float const elapsed) override
    {
        auto const keyboard = getGame()->input().keyboard();
        if (keyboard->justPressed(jt::KeyCode::F1) || keyboard->justPressed(jt::KeyCode::Escape)) {
            getGame()->stateManager().switchState(std::make_shared<StateSelect>());
        }

        m_scene->update(elapsed);
        m_title->update(elapsed);
    }

    void onDraw() const override
    {
        m_scene->draw();
        m_title->draw(renderTarget());
    }
};

#endif // DEMO_STATE_COLLISION_HPP
