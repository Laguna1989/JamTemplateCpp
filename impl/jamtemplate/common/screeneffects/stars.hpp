#ifndef JAMTEMPLATE_STARS_HPP
#define JAMTEMPLATE_STARS_HPP

#include <color/color.hpp>
#include <game_object.hpp>
#include <screeneffects/star.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

namespace jt {

///  A starfield screen effect
class Stars : public jt::GameObject {
public:
    ///  Create a starfield effect
    /// \param count Number of stars
    /// \param col Color of the stars
    /// \param screenSizeHint Hint for the size of the screen
    Stars(std::size_t count, jt::Color const& col, jt::Vector2f const& screenSizeHint);

    ///  set the starfield enabled or disabled
    void setEnabled(bool enable);

    ///  set the movement factor of the starfield
    void setCamMovementFactor(float factor);

    ///  set the z layer of the starfield
    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Color m_color;
    jt::Vector2f m_screenSizeHint;

    bool m_enabled { true };

    std::vector<std::unique_ptr<Star>> m_stars;
};
} // namespace jt

#endif // JAMTEMPLATE_STARS_HPP
