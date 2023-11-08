#ifndef JAMTEMPLATE_VIGNETTE_HPP
#define JAMTEMPLATE_VIGNETTE_HPP

#include <color/color.hpp>
#include <game_object.hpp>
#include <vector.hpp>

namespace jt {

class Sprite;

class Vignette : public jt::GameObject {
public:
    explicit Vignette(jt::Vector2f const& size);
    void setEnabled(bool enabled);

    void setColor(jt::Color const& col);
    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    bool m_enabled { true };
    std::shared_ptr<jt::Sprite> m_vignette { nullptr };
    jt::Vector2f m_size;
};
} // namespace jt
#endif // JAMTEMPLATE_VIGNETTE_HPP
