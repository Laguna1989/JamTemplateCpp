#include "state_simplex_noise.hpp"
#include "../state_select.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"
#include "shape.hpp"

void StateSimplexNoise::doInternalCreate() { }
void StateSimplexNoise::doInternalUpdate(float elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }
    m_z += elapsed * 0.9f;
}
void StateSimplexNoise::doInternalDraw() const
{
    jt::Shape shape;
    shape.makeRect(jt::Vector2f { 2.0f, 2.0f }, getGame()->gfx().textureManager());

    std::vector<float> randomNumbers(100 * 100, 0.0f);
    for (auto i = 0; i != 100; ++i) {
        for (auto j = 0; j != 100; ++j) {
            float v1 = noiseL1.eval(i / 100.0f, j / 100.0f, m_z);
            float v2 = noiseL2.eval(i / 50.0f, j / 50.0f, -m_z);
            float v3 = noiseL2.eval(i / 25.0f, j / 25.0f, -m_z);
            float v = 0.3f * v1 + 0.3f * v2 + 0.6f * v3;
            v = jt::MathHelper::clamp(v, 0.0f, 1.0f);
            randomNumbers[i + j * 100] = v;
        }
    }

    auto max = *std::max_element(randomNumbers.begin(), randomNumbers.end());

    for (auto i = 0; i != 100; ++i) {
        for (auto j = 0; j != 100; ++j) {
            shape.setPosition(jt::Vector2f { 32 + i * 2.0f, 32 + j * 2.0f });

            auto v = randomNumbers[i + j * 100] / max;
            auto vu = static_cast<std::uint8_t>(v * 255.0f);
            shape.setColor(jt::Color { vu, vu, vu, 255 });

            shape.update(0.1f);
            shape.draw(getGame()->gfx().target());
        }
    }
}
