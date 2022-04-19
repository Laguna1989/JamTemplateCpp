#ifndef JAMTEMPLATE_CLOUDS_HPP
#define JAMTEMPLATE_CLOUDS_HPP

#include <game_object.hpp>
#include <vector.hpp>

namespace jt {

class Sprite;

// TODO extract into screen wrapping sprite group
class Clouds : public jt::GameObject {
public:
    explicit Clouds(jt::Vector2f const& velocity);

    void setEnabled(bool enabled);

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
