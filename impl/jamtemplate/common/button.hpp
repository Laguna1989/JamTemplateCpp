﻿#ifndef GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD
#define GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD

#include "game_object.hpp"
#include "vector.hpp"
#include <functional>
#include <memory>
#include <vector>

namespace jt {
class Animation;
class Sprite;
class DrawableInterface;

class Button : public GameObject {
public:
    using Sptr = std::shared_ptr<Button>;

    Button(jt::Vector2u s = jt::Vector2u { 16, 16 });
    ~Button();

    Button(const Button& b) = delete;
    Button(Button&& b) = default;

    void setDrawable(std::shared_ptr<DrawableInterface> sprt);

    void addCallback(std::function<void(void)> cb);

    void clearCallbacks();
    size_t getCallbackCount() const;

    bool IsMouseOver();

    void setVisible(bool v);
    bool getVisible() const;

    void setActive(bool v);
    bool getActive() const;

    void setPosition(jt::Vector2 const& v);
    jt::Vector2 getPosition(void) const;

private:
    std::shared_ptr<Animation> m_background { nullptr };
    std::shared_ptr<jt::Sprite> m_disabledOverlay { nullptr };
    std::shared_ptr<DrawableInterface> m_drawable { nullptr };
    std::vector<std::function<void(void)>> m_callbacks {};
    jt::Vector2 m_pos { 0.0f, 0.0f };

    bool m_isVisible { true };
    bool m_isActive { true };

    void doDraw() const override;

    bool isOver(jt::Vector2 const& mousePosition);

    void doUpdate(float elapsed) override;
};
} // namespace jt

#endif