
#include "state_offset_origin.hpp"
std::string StateOffsetOrigin::getName() const { return "Offset Origin"; }
void StateOffsetOrigin::onCreate()
{
    for (auto i = 0; i != 4; ++i) {
        for (auto j = 0; j != 3; ++j) {
            jt::OriginMode const origin = static_cast<jt::OriginMode>(j);

            for (auto k : { true, false }) {

                jt::Vector2f const pos { (i + 0.5f) * 48.0f + k * 192.0f, (j + 1.0f) * 48.0f };

                auto shape = std::make_shared<jt::Shape>();
                shape->makeRect(jt::Vector2f { 2.0f, 24.0f }, textureManager());
                shape->setOrigin(origin);
                shape->setPosition(pos);
                shape->setRotation(90.0f * i);
                m_shapes.push_back(shape);

                auto sprite = std::make_shared<jt::Sprite>("#g#32#200", textureManager());
                sprite->setOrigin(origin);
                sprite->setPosition(pos);
                sprite->setRotation(90.0f * i);
                sprite->setColor(jt::colors::Red);
                if (k) {
                    sprite->setScale(jt::Vector2f { 0.5f, 1.0f });
                }

                m_sprites.push_back(sprite);
            }
        }
    }
}
void StateOffsetOrigin::onEnter() { }

void StateOffsetOrigin::onUpdate(float const elapsed)
{
    for (auto const& s : m_shapes) {
        s->update(elapsed);
    }
    for (auto const& s : m_sprites) {
        s->update(elapsed);
    }
}
void StateOffsetOrigin::onDraw() const
{
    for (auto const& s : m_sprites) {
        s->draw(renderTarget());
    }

    for (auto const& s : m_shapes) {
        s->draw(renderTarget());
    }
}
