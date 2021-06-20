#include "button.hpp"
#include "animation.hpp"
#include "drawable_impl.hpp"
#include "drawable_interface.hpp"
#include "game_interface.hpp"
#include "game_object.hpp"
#include "input_manager.hpp"
#include "vector.hpp"
#include <functional>
#include <memory>
#include <string>

namespace jt {

Button::Button(jt::Vector2u s)
{
    std::string buttonImageName = "#b#" + std::to_string(s.x()) + "#" + std::to_string(s.y());
    m_background = std::make_shared<jt::Animation>();
    m_background->add(buttonImageName, "normal", s, { 0 }, 1);
    m_background->add(buttonImageName, "over", s, { 1 }, 1);
    m_background->add(buttonImageName, "down", s, { 2 }, 1);
    m_background->play("normal");
    m_background->setIgnoreCamMovement(true);
}
Button::~Button()
{
    m_drawable = nullptr;
    m_background = nullptr;
    m_callbacks.clear();
}

void Button::setDrawable(std::shared_ptr<DrawableInterface> sprt) { m_drawable = sprt; }

void Button::addCallback(std::function<void(void)> cb) { m_callbacks.push_back(cb); }

void Button::clearCallbacks() { m_callbacks.clear(); }
size_t Button::getCallbackCount() const { return m_callbacks.size(); }

bool Button::IsMouseOver()
{
    if (getGame()->input() == nullptr) {
        return false;
    }
    return isOver(getGame()->input()->mouse()->getMousePositionScreen());
}

void Button::setVisible(bool v) { m_visible = v; }

bool Button::getVisible() const { return m_visible; }

void Button::setPosition(jt::Vector2 const& v) { m_pos = v; }

jt::Vector2 Button::getPosition() const { return m_pos; }

void Button::doDraw() const
{
    if (!m_visible) {
        return;
    }
    m_background->draw(getGame()->getRenderTarget());
    if (m_drawable)
        m_drawable->draw(getGame()->getRenderTarget());
}

bool Button::isOver(jt::Vector2 const& mousePosition)
{
    float px = m_background->getPosition().x();
    float py = m_background->getPosition().y();

    float w = m_background->getGlobalBounds().width();
    float h = m_background->getGlobalBounds().height();
    return (mousePosition.x() > px && mousePosition.x() <= px + w && mousePosition.y() > py
        && mousePosition.y() <= py + h);
}

void Button::doUpdate(float elapsed)
{
    m_background->update(elapsed);
    m_background->setPosition(m_pos);
    if (m_drawable) {
        m_drawable->setPosition(m_pos);
        m_drawable->update(elapsed);
    }

    if (IsMouseOver()) {
        if (getGame()->input()->mouse()->pressed(jt::MouseButtonCode::MBLeft)) {
            m_background->play("down");
        } else {
            m_background->play("over");
        }

        if (getGame()->input()->mouse()->justReleased(jt::MouseButtonCode::MBLeft)) {
            if (m_visible) {
                for (auto& cb : m_callbacks) {
                    cb();
                }
            }
        }
    } else {
        m_background->play("normal");
    }
}

} // namespace jt
