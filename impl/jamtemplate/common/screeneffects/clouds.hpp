#ifndef JAMTEMPLATE_CLOUDS_HPP
#define JAMTEMPLATE_CLOUDS_HPP

#include <game_object.hpp>
#include <vector.hpp>

namespace jt {

class Sprite;

// TODO extract into screen wrapping sprite group

/// A overlay of clouds that move with a given velocity as a screen effect
class Clouds : public jt::GameObject {
public:
    /// Create the clouds with a given velocity
    /// \param velocity velocity of the clouds
    explicit Clouds(jt::Vector2f const& velocity);

    /// Set the screen effects enabled or disabled
    /// \param enabled true if enabled, false otherwise
    void setEnabled(bool enabled);

    /// Set the z layer of the clouds screen effect
    void setZ(int zLayer);

private:
    mutable std::shared_ptr<jt::Sprite> m_layer1;
    mutable std::shared_ptr<jt::Sprite> m_layer2;
    mutable std::shared_ptr<jt::Sprite> m_layer3;

    jt::Vector2f m_velocity;

    bool m_enabled { true };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

} // namespace jt

#endif // JAMTEMPLATE_CLOUDS_HPP
