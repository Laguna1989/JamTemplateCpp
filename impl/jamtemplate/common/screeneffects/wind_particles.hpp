#ifndef INC_JAMTEMPLATE_WIND_PARTICLES_HPP
#define INC_JAMTEMPLATE_WIND_PARTICLES_HPP

#include "game_object.hpp"
#include "shape.hpp"

namespace jt {
class WindParticles : public jt::GameObject {

public:
    WindParticles(jt::Vector2f const& screenSize, std::vector<jt::Color> const& colors);
    float m_windSpeed { 1.0f };

    void setEnabled(bool enabled);

    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
    std::vector<float> m_factors;
    jt::Vector2f m_screenSize { 0.0f, 0.0f };
    std::vector<jt::Color> m_colors;

    bool m_enabled { true };
};

} // namespace jt

#endif // INC_JAMTEMPLATE_WIND_PARTICLES_HPP
