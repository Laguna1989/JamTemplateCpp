#ifndef GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD
#define GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD

#include "GameObject.hpp"
#include "Vector.hpp"
#include <functional>
#include <memory>

namespace jt {
class Animation;
class DrawableImpl;

class Button : public GameObject {
public:
    using Sptr = std::shared_ptr<Button>;

    Button(jt::Vector2u s = jt::Vector2u { 16, 16 });
    ~Button();

    Button(const Button& b) = delete;
    Button(Button&& b) = default;

    void setDrawable(std::shared_ptr<DrawableImpl> sprt);

    void addCallback(std::function<void(void)> cb);

    void clearCallbacks();
    size_t getCallbackCount() const;

    bool IsMouseOver();

    void setVisible(bool v);

    void setPosition(jt::Vector2 const& v);

private:
    std::shared_ptr<Animation> m_background;
    std::shared_ptr<DrawableImpl> m_drawable { nullptr };
    std::vector<std::function<void(void)>> m_callbacks;
    jt::Vector2 m_pos;

    bool m_visible { true };

    void doDraw() const override;

    bool isOver(jt::Vector2 const& mp);

    void doUpdate(float elapsed) override;
};
} // namespace jt

#endif
