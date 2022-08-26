#ifndef JAMTEMPLATE_STARS_HPP
#define JAMTEMPLATE_STARS_HPP

#include <color/color.hpp>
#include <game_object.hpp>
#include <screeneffects/star.hpp>
#include <vector.hpp>
#include <memory>
#include <vector>

namespace jt {

class Stars : public jt::GameObject {
public:
    Stars(std::size_t count, jt::Color const& col, jt::Vector2f const& screenSizeHint);
    void setEnabled(bool enable);
    void setCamMovementFactor(float factor);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_screenSizeHint;
    jt::Color m_color;

    bool m_enabled { true };

    std::vector<std::unique_ptr<Star>> m_stars;
};
} // namespace jt

#endif // JAMTEMPLATE_STARS_HPP
