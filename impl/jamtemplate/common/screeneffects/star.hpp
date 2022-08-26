#ifndef INC_1HGJ379_STAR_HPP
#define INC_1HGJ379_STAR_HPP

#include <game_object.hpp>
#include <shape.hpp>

namespace jt {
class Star : public jt::GameObject {
public:
    void setPosition(jt::Vector2f const& screenSizeHint);
    void setColor(jt::Color const& col);
    void setCamMovementFactor(float factor);

private:
    std::shared_ptr<jt::Shape> m_shape;

    float m_rand1;
    float m_rand2;
    float m_rand3;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

} // namespace jt

#endif // INC_1HGJ379_STAR_HPP
