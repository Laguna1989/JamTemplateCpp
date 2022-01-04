#include "button.hpp"
#include "animation.hpp"
#include "drawable_interface.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "sprite.hpp"
#include "texture_manager_interface.hpp"
#include "vector.hpp"
#include <functional>
#include <memory>
#include <string>

namespace jt {

Button::Button(Vector2u const& size, jt::TextureManagerInterface& textureManager)
{
    std::string buttonImageName = "#b#" + std::to_string(size.x) + "#" + std::to_string(size.y);
    m_background = std::make_shared<jt::Animation>();
    m_background->add(buttonImageName, "normal", size, { 0 }, 1, textureManager);
    m_background->add(buttonImageName, "over", size, { 1 }, 1, textureManager);
    m_background->add(buttonImageName, "down", size, { 2 }, 1, textureManager);
    m_background->play("normal");
    m_background->setIgnoreCamMovement(true);

    m_disabledOverlay = std::make_shared<jt::Sprite>(
        "#f#" + std::to_string(size.x) + "#" + std::to_string(size.y), textureManager);
    m_disabledOverlay->setColor(jt::Color { 100, 100, 100, 150 });
}

Button::~Button()
{
    m_drawable = nullptr;
    m_background = nullptr;
    m_callbacks.clear();
}

void Button::setDrawable(std::shared_ptr<DrawableInterface> drawable) { m_drawable = drawable; }
void Button::addCallback(std::function<void(void)> callback)
{
    m_callbacks.emplace_back(std::move(callback));
}
void Button::clearCallbacks() { m_callbacks.clear(); }
std::size_t Button::getCallbackCount() const { return m_callbacks.size(); }
bool Button::isMouseOver() { return isOver(getGame()->input().mouse()->getMousePositionScreen()); }
void Button::setVisible(bool isVisible) { m_isVisible = isVisible; }
bool Button::getVisible() const { return m_isVisible; }
void Button::setPosition(jt::Vector2f const& newPosition) { m_pos = newPosition; }
jt::Vector2f Button::getPosition() const { return m_pos; }
void Button::doDraw() const
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
bool Button::isOver(jt::Vector2f const& mousePosition)
{
    if (!m_isActive) {
        return false;
    }

    float px = m_background->getPosition().x;
    float py = m_background->getPosition().y;

    float w = m_background->getGlobalBounds().width;
    float h = m_background->getGlobalBounds().height;
    return (mousePosition.x > px && mousePosition.x <= px + w && mousePosition.y > py
        && mousePosition.y <= py + h);
}

void Button::doUpdate(float elapsed)
{
    m_disabledOverlay->setPosition((m_pos));
    m_disabledOverlay->update(elapsed);

    m_background->setPosition(m_pos);
    m_background->update(elapsed);

    if (m_drawable) {
        m_drawable->setPosition(m_pos);
        m_drawable->update(elapsed);
    }

    if (getGame()->input().mouse() == nullptr) {
        return;
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
}
bool Button::getActive() const { return m_isActive; }
void Button::setActive(bool isActive) { m_isActive = isActive; }

} // namespace jt
