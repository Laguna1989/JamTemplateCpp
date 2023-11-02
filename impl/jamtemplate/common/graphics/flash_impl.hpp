#ifndef JAMTEMPLATE_FLASH_INTERFACE_HPP
#define JAMTEMPLATE_FLASH_INTERFACE_HPP

#include <color/color.hpp>
#include <render_target_layer.hpp>
#include <memory>

namespace jt {
class FlashImpl {
public:
    void drawFlash(std::shared_ptr<jt::RenderTargetLayer> sptr) const;
    void doFlash(float t, jt::Color col);

    /// Set the flash color of the drawable
    /// \param col the color
    void doSetFlashColor(jt::Color const& col);

    /// Get the flash color of the drawable
    /// \return the color
    jt::Color doGetFlashColor() const;

    void updateFlash(float elapsed);

private:
    virtual void doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> sptr) const = 0;

    virtual void doFlashImpl(float /*t*/, jt::Color /*col = jt::colors::White*/) { }

    float m_flashTimer { -1.0f };
    float m_maxFlashTimer { -1.0f };

    jt::Color m_flashColor { jt::colors::White };
};

} // namespace jt

#endif // JAMTEMPLATE_FLASH_INTERFACE_HPP
