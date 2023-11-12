#ifndef INC_1HGJ379_STAR_HPP
#define INC_1HGJ379_STAR_HPP

#include "sprite.hpp"
#include <game_object.hpp>
#include <shape.hpp>

namespace jt {
class Star : public jt::GameObject {
public:
    void setPosition(jt::Vector2f const& screenSizeHint);
    void setColor(jt::Color const& col);
    void setCamMovementFactor(float factor);

    void setZ(int zLayer);

private:
    std::shared_ptr<jt::Shape> m_shape;
    std::shared_ptr<jt::Sprite> m_glow;
    std::uint8_t m_starAlphaMax { 100u };

    float m_rand1 { 0.0f };
    float m_rand2 { 0.0f };
    float m_rand3 { 0.0f };
    jt::Vector2f m_glowOffset { 0.0f, 0.0f };
    int m_glowSize { 0 };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
    void updateStarBrightness();
};

} // namespace jt

#endif // INC_1HGJ379_STAR_HPP
