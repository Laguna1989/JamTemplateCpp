#include "clouds.hpp"
#include <game_interface.hpp>
#include <sprite.hpp>
#include <iostream>

jt::Clouds::Clouds(jt::Vector2f const& velocity)
    : m_velocity { velocity }
{
}

void jt::Clouds::doCreate()
{
    m_layer1 = std::make_shared<jt::Sprite>("assets/clouds1.png", textureManager());
    m_layer1->setColor(jt::Color { 255, 255, 255, 110 });
    m_layer1->setBlendMode(jt::BlendMode::ALPHA);

    m_layer2 = std::make_shared<jt::Sprite>("assets/clouds2.png", textureManager());
    m_layer2->setColor(jt::Color { 255, 255, 255, 90 });
    m_layer2->setBlendMode(jt::BlendMode::ALPHA);

    m_layer3 = std::make_shared<jt::Sprite>("assets/clouds3.png", textureManager());
    m_layer3->setColor(jt::Color { 255, 255, 255, 100 });

    m_layer3->setBlendMode(jt::BlendMode::ALPHA);
}

void wrapLayerPosition(std::shared_ptr<jt::Sprite>& layer)
{
    auto bounds = layer->getGlobalBounds();

    if (bounds.left + layer->getStaticCamOffset().x <= -bounds.width) {
        layer->setPosition(jt::Vector2f { bounds.left + bounds.width, bounds.top });
    } else if (bounds.left + layer->getStaticCamOffset().x > bounds.width) {
        layer->setPosition(jt::Vector2f { bounds.left - bounds.width, bounds.top });
    }

    if (bounds.top + layer->getStaticCamOffset().y <= -bounds.height) {
        layer->setPosition(jt::Vector2f { bounds.left, bounds.top + bounds.height });
    } else if (bounds.top + layer->getStaticCamOffset().y > bounds.height) {
        layer->setPosition(jt::Vector2f { bounds.left, bounds.top - bounds.height });
    }
}

void jt::Clouds::doUpdate(float const elapsed)
{
    m_layer1->setPosition(m_layer1->getPosition() + m_velocity * elapsed * 1.12f);
    m_layer2->setPosition(m_layer2->getPosition() + m_velocity * elapsed * 2.3f);
    m_layer3->setPosition(m_layer3->getPosition() + m_velocity * elapsed * 3.7f);

    wrapLayerPosition(m_layer1);
    wrapLayerPosition(m_layer2);
    wrapLayerPosition(m_layer3);

    m_layer1->update(elapsed);
    m_layer2->update(elapsed);
    m_layer3->update(elapsed);
}

void drawLayer(std::shared_ptr<jt::RenderTargetInterface> rt, std::shared_ptr<jt::Sprite> layer)
{
    auto const oldPos = layer->getPosition();
    for (auto j = -1; j != 2; ++j) {
        for (auto i = -1; i != 2; ++i) {
            layer->setPosition(oldPos
                + jt::Vector2f {
                    i * layer->getGlobalBounds().width, j * layer->getGlobalBounds().height });
            layer->update(0.0f);
            layer->draw(rt);
        }
    }
    layer->setPosition(oldPos);
    layer->update(0.0f);
}

void jt::Clouds::doDraw() const
{
    if (m_enabled) {
        drawLayer(renderTarget(), m_layer1);
        drawLayer(renderTarget(), m_layer2);
        drawLayer(renderTarget(), m_layer3);
    }
}

void jt::Clouds::setEnabled(bool enabled) { m_enabled = enabled; }

void jt::Clouds::setZ(int zLayer)
{
    m_layer1->setZ(zLayer);
    m_layer2->setZ(zLayer);
    m_layer3->setZ(zLayer);
}
