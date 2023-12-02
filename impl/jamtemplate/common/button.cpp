#include "button.hpp"
#include <animation.hpp>
#include <game_interface.hpp>
#include <graphics/drawable_interface.hpp>
#include <input/input_manager.hpp>
#include <sprite.hpp>
#include <texture_manager_interface.hpp>
#include <vector.hpp>
#include <memory>
#include <string>

jt::Button::Button(jt::Vector2u const& size, jt::TextureManagerInterface& textureManager)
{
    std::string buttonImageName = "#b#" + std::to_string(size.x) + "#" + std::to_string(size.y);
    m_background = std::make_shared<jt::Animation>();
    m_background->add(buttonImageName, "normal", size, { 0 }, 1, textureManager);
    m_background->add(buttonImageName, "over", size, { 1 }, 1, textureManager);
    m_background->add(buttonImageName, "down", size, { 2 }, 1, textureManager);
    m_background->play("normal");
    m_background->setIgnoreCamMovement(true);
    m_background->setOrigin(jt::OriginMode::CENTER);
    m_background->setOffset(jt::Vector2f { size.x / 2.0f, size.y / 2.0f });

    m_disabledOverlay = std::make_shared<jt::Sprite>(
        "#f#" + std::to_string(size.x) + "#" + std::to_string(size.y), textureManager);
    m_disabledOverlay->setColor(jt::Color { 100, 100, 100, 150 });
}

jt::Button::~Button()
{
    m_drawable = nullptr;
    m_background = nullptr;
    m_callbacks.clear();
}

void jt::Button::setDrawable(std::shared_ptr<jt::DrawableInterface> drawable)
{
    m_drawable = drawable;
}

void jt::Button::addCallback(std::function<void(void)> const& callback)
{
    m_callbacks.emplace_back(std::move(callback));
}

void jt::Button::clearCallbacks() { m_callbacks.clear(); }

std::size_t jt::Button::getCallbackCount() const { return m_callbacks.size(); }

bool jt::Button::isMouseOver()
{
    return isOver(getGame()->input().mouse()->getMousePositionScreen());
}

void jt::Button::setVisible(bool isVisible) noexcept { m_isVisible = isVisible; }

bool jt::Button::getVisible() const noexcept { return m_isVisible; }

void jt::Button::setPosition(jt::Vector2f const& newPosition) noexcept
{
    m_pos = newPosition;
    m_background->setPosition(m_pos);
    if (m_drawable) {
        m_drawable->setPosition(m_pos);
    }
}

jt::Vector2f jt::Button::getPosition() const noexcept { return m_pos; }

void jt::Button::doDraw() const
{
    if (!m_isVisible) {
        return;
    }

    m_background->draw(getGame()->gfx().target());
    if (m_drawable) {
        m_drawable->draw(getGame()->gfx().target());
    }

    if (!m_isActive) {
        m_disabledOverlay->draw(getGame()->gfx().target());
    }
}

bool jt::Button::isOver(jt::Vector2f const& mousePosition)
{
    if (!m_isActive) {
        return false;
    }

    float const px = m_background->getPosition().x;
    float const py = m_background->getPosition().y;

    float const w = m_background->getGlobalBounds().width;
    float const h = m_background->getGlobalBounds().height;
    return (mousePosition.x > px && mousePosition.x <= px + w && mousePosition.y > py
        && mousePosition.y <= py + h);
}

void jt::Button::doUpdate(float elapsed)
{
    if (m_drawable) {
        m_drawable->update(elapsed);
    }

    if (isMouseOver()) {
        if (getGame()->input().mouse()->pressed(jt::MouseButtonCode::MBLeft)) {
            m_background->play("down");
        } else {
            m_background->play("over");
        }

        if (getGame()->input().mouse()->justReleased(jt::MouseButtonCode::MBLeft)) {
            if (m_isVisible) {
                for (auto& cb : m_callbacks) {
                    cb();
                }
            }
        }

    } else {
        m_background->play("normal");
    }

    m_disabledOverlay->update(elapsed);

    m_disabledOverlay->setPosition(m_background->getPosition());
    m_background->update(elapsed);
}

bool jt::Button::getActive() const { return m_isActive; }

void jt::Button::setActive(bool isActive) { m_isActive = isActive; }

std::shared_ptr<jt::DrawableInterface> jt::Button::getBackground() { return m_background; }

std::shared_ptr<jt::DrawableInterface> jt::Button::getDrawable() const { return m_drawable; }
