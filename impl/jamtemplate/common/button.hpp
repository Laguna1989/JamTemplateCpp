#ifndef JAMTEMPLATE_BUTTON_HPP
#define JAMTEMPLATE_BUTTON_HPP

#include <game_object.hpp>
#include <vector.hpp>
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
    /// \param size size of the button in pixel
    /// \param textureManager texture manager
    Button(Vector2u const& size, jt::TextureManagerInterface& textureManager);
    ~Button() override;

    Button(Button const& b) = delete;
    Button(Button&& b) = default;

    /// Set the drawable (e.g. the icon or text of the button)
    /// \param drawable the drawable to be used
    void setDrawable(std::shared_ptr<DrawableInterface> drawable);

    /// Get the drawable (e.g. the icon or text of the button)
    /// \return the drawable. Cann be null if no drawable was set
    std::shared_ptr<jt::DrawableInterface> getDrawable() const;

    /// Add a callback to be invoked when the button is clicked
    /// \param callback the callback to be added
    void addCallback(std::function<void(void)> const& callback);

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
    void setVisible(bool isVisible) noexcept;

    /// Get the visibility
    /// \return true if visible, false otherwise
    bool getVisible() const noexcept;

    /// Set the button active status (inactive buttons are drawn but can not be clicked)
    /// \param isActive
    void setActive(bool isActive);

    /// Get the active status of the button
    /// \return
    bool getActive() const;

    /// Set the position of the Button
    /// \param newPosition
    void setPosition(jt::Vector2f const& newPosition) noexcept;

    /// Get the position of the Button
    jt::Vector2f getPosition(void) const noexcept;

    std::shared_ptr<jt::DrawableInterface> getBackground();

private:
    std::shared_ptr<jt::Animation> m_background { nullptr };
    std::shared_ptr<jt::Sprite> m_disabledOverlay { nullptr };
    std::shared_ptr<jt::DrawableInterface> m_drawable { nullptr };
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
