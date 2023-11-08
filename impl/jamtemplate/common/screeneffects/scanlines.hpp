#ifndef JAMTEMPLATE_SCANLINES_HPP
#define JAMTEMPLATE_SCANLINES_HPP

#include <color/color.hpp>
#include <game_object.hpp>
#include <vector.hpp>
#include <memory>

namespace jt {

class Shape;

class ScanLines : public jt::GameObject {
public:
    ScanLines(jt::Vector2f const& shapeSize, std::size_t shapeCount);

    void setEnabled(bool enable);

    void setColor(jt::Color const& col);

    void setZ(int zLayer);

private:
    bool m_enabled { true };
    mutable std::shared_ptr<jt::Shape> m_shape;
    jt::Vector2f m_shapeSize;
    std::size_t m_shapeCount;

    void doCreate() override;
    void doDraw() const override;
};

} // namespace jt

#endif // JAMTEMPLATE_SCANLINES_HPP
