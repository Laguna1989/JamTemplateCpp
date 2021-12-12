#include "state_simplex_noise.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"
#include "shape.hpp"
#include "state_select.hpp"
#include <iostream>

void StateSimplexNoise::doInternalCreate() { }
void StateSimplexNoise::doInternalUpdate(float elapsed)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
    m_z += elapsed * 0.9f;
}
void StateSimplexNoise::doInternalDraw() const
{
    auto shape = std::make_shared<jt::Shape>();
    shape->makeRect(jt::Vector2f { 2.0f, 2.0f }, getGame()->getTextureManager());

    for (auto i = 0; i != 100; ++i) {
        for (auto j = 0; j != 100; ++j) {
            shape->setPosition(jt::Vector2f { 32 + i * 2.0f, 32 + j * 2.0f });
            shape->update(0.1f);
            float v = noise.eval(i / 100.0f, j / 100.0f, m_z);
            v = jt::MathHelper::clamp(v, 0.0f, 1.0f);
            auto vu = static_cast<std::uint8_t>(1 + v * 254.0f);
            shape->setColor(jt::Color { vu, vu, vu, 255 });
            shape->draw(getGame()->getRenderTarget());
        }
    }
}
