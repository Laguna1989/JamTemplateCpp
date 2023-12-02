#include "state_3d_noise.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <shape.hpp>
#include <state_select.hpp>
#include <algorithm>

void State3DNoise::onCreate() { }

void State3DNoise::onEnter() { }

void State3DNoise::onUpdate(float elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
    m_z += elapsed * 0.9f;
}

void State3DNoise::onDraw() const
{
    jt::Shape shape;
    shape.makeRect(jt::Vector2f { 2.0f, 2.0f }, textureManager());

    std::vector<float> randomNumbers(100 * 100, 0.0f);
    for (auto i = 0; i != 100; ++i) {
        for (auto j = 0; j != 100; ++j) {
            float const v1 = noiseL1.eval(i / 100.0f, j / 100.0f, m_z);
            float const v2 = noiseL2.eval(i / 50.0f, j / 50.0f, -m_z);
            float const v3 = noiseL2.eval(i / 25.0f, j / 25.0f, -m_z);
            float v = 0.3f * v1 + 0.3f * v2 + 0.6f * v3;
            v = std::clamp(v, 0.0f, 1.0f);
            randomNumbers[i + j * 100] = v;
        }
    }

    auto const max = *std::max_element(randomNumbers.cbegin(), randomNumbers.cend());

    for (auto i = 0; i != 100; ++i) {
        for (auto j = 0; j != 100; ++j) {
            shape.setPosition(jt::Vector2f { 32 + i * 2.0f, 32 + j * 2.0f });

            auto const v = randomNumbers[i + j * 100] / max;
            auto const vu = static_cast<std::uint8_t>(v * 255.0f);
            shape.setColor(jt::Color { vu, vu, vu, 255 });

            shape.update(0.1f);
            shape.draw(renderTarget());
        }
    }
}
