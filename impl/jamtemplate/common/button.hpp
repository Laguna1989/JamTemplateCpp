#ifndef GUARD_JAMTEMPLATE_BUTTON_HPP_GUARD
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
class TextureManagerInterface;

class Button : public GameObject {
public:
    using Sptr = std::shared_ptr<Button>;

    /// Constructor, creates a button with the given size
    /// \param size the size of the button in pixel
    Button(Vector2u const& size, jt::TextureManagerInterface& textureManager);
    ~Button();

    Button(const Button& b) = delete;
    Button(Button&& b) = default;

    /// Set the drawable (e.g. the icon or text of the button)
    /// \param drawable the drawable to be used
    void setDrawable(std::shared_ptr<DrawableInterface> drawable);

    /// Add a callback to be invoked when the button is clicked
    /// \param callback the callback to be added
    void addCallback(std::function<void(void)> callback);

    /// Clear the list of callbacks
    void clearCallbacks();

    /// Get the number of callbacks currently registered
    /// \return the number of callbacks
    std::size_t getCallbackCount() const;

    /// Check if the mouse is over the button
    /// \return true if it is, false otherwise
    bool isMouseOver();

    /// Set the visibility of the button (invisible buttons can not be clicked)
    /// \param isVisible
    void setVisible(bool isVisible);

    /// Get the visibility
    /// \return true if visible, false otherwise
    bool getVisible() const;

    /// Set the button active status (inactive buttons are drawn but can not be clicked)
    /// \param isActive
    void setActive(bool isActive);

    /// Get the active status of the button
    /// \return
    bool getActive() const;

    /// Set the position of the Button
    /// \param newPosition
    void setPosition(jt::Vector2f const& newPosition);

    /// Get the position of the Button
    jt::Vector2f getPosition(void) const;

private:
    std::shared_ptr<Animation> m_background { nullptr };
    std::shared_ptr<jt::Sprite> m_disabledOverlay { nullptr };
    std::shared_ptr<DrawableInterface> m_drawable { nullptr };
    std::vector<std::function<void(void)>> m_callbacks {};
    jt::Vector2f m_pos { 0.0f, 0.0f };

    bool m_isVisible { true };
    bool m_isActive { true };

    void doDraw() const override;

    bool isOver(jt::Vector2f const& mousePosition);

    void doUpdate(float elapsed) override;
};
} // namespace jt

#endif
