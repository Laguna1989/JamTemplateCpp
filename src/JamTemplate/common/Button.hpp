#ifndef GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD
#define GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD

#include "GameInterface.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "SmartAnimation.hpp"
#include "SmartDrawable.hpp"
#include "Vector.hpp"
#include <functional>
#include <memory>
#include <string>

namespace jt {
class Button : public GameObject {
public:
    using Sptr = std::shared_ptr<Button>;

    Button(jt::Vector2u s = jt::Vector2u { 16, 16 })
    {
        std::string buttonImageName = "#b#" + std::to_string(s.x()) + "#" + std::to_string(s.y());
        m_background = std::make_shared<jt::SmartAnimation>();
        m_background->add(buttonImageName, "normal", s, { 0 }, 1);
        m_background->add(buttonImageName, "over", s, { 1 }, 1);
        m_background->add(buttonImageName, "down", s, { 2 }, 1);
        m_background->play("normal");
        m_background->setIgnoreCamMovement(true);
    }
    ~Button()
    {
        // std::cout << "button destructor\n";
        // std::cout << m_drawable << "\n";
        m_drawable = nullptr;
        // std::cout << "button destructor half 1\n";
        m_background = nullptr;
        // std::cout << "button destructor half 2\n";
        m_callbacks.clear();
        // std::cout << "button destructor end\n";
    }

    Button(const Button& b) = delete;
    Button(Button&& b) = default;

    void setDrawable(SmartDrawable::Sptr sprt) { m_drawable = sprt; }

    void addCallback(std::function<void(void)> cb) { m_callbacks.push_back(cb); }

    void clearCallbacks() { m_callbacks.clear(); }
    size_t getCallbackCount() const { return m_callbacks.size(); }

    bool IsMouseOver()
    {
        return isOver(
            InputManager::getMousePositionScreen().x(), InputManager::getMousePositionScreen().y());
    }

    void setVisible(bool v) { m_visible = v; }

    void setPosition(jt::Vector2 const& v) { m_pos = v; }

private:
    std::shared_ptr<SmartAnimation> m_background;
    std::shared_ptr<SmartDrawable> m_drawable { nullptr };
    std::vector<std::function<void(void)>> m_callbacks;
    jt::Vector2 m_pos;

    bool m_visible { true };

    void doDraw() const override
    {
        m_background->draw(getGame()->getRenderTarget());
        if (m_drawable)
            m_drawable->draw(getGame()->getRenderTarget());
    }

    bool isOver(float mx, float my)
    {
        float px = m_background->getPosition().x();
        float py = m_background->getPosition().y();

        float w = m_background->getGlobalBounds().width();
        float h = m_background->getGlobalBounds().height();
        return (mx > px && mx <= px + w && my > py && my <= py + h);
    }

    void doUpdate(float elapsed) override
    {
        m_background->update(elapsed);
        m_background->setPosition(m_pos);
        if (m_drawable) {
            m_drawable->setPosition(m_pos);
            m_drawable->update(elapsed);
        }

        if (isOver(jt::InputManager::getMousePositionScreen().x(),
                jt::InputManager::getMousePositionScreen().y())) {
            if (jt::InputManager::pressed(jt::MouseButtonCode::MBLeft)) {
                m_background->play("down");
            } else {
                m_background->play("over");
            }

            if (jt::InputManager::justReleased(jt::MouseButtonCode::MBLeft)) {
                if (m_visible) {
                    for (auto& cb : m_callbacks) {
                        std::cout << "callback\n";
                        cb();
                    }
                }
            }
        } else {
            // std::cout << "not over" << std::endl;
            m_background->play("normal");
        }
    }
};
} // namespace jt

#endif
