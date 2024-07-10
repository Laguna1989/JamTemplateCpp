#ifndef FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HORIZONTAL_HPP
#define FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HORIZONTAL_HPP

#include <animation.hpp>
#include <game_object.hpp>

namespace jt {

///  A mario clouds screen effect
class MarioCloudsHorizontal : public jt::GameObject {
public:
    ///  Constructor for mario clouds screen effect
    MarioCloudsHorizontal(
        std::size_t numberOfClouds, jt::Vector2f const& screenArea, jt::Vector2f const& margin);

    ///  set te scale of the clouds
    void setScale(jt::Vector2f const& scale);

    ///  set the offset of the shadow
    void setShadowOffset(jt::Vector2f const& offset);

    ///  set the z layer of the mario clouds
    void setZ(int zLayer);

    ///  set the effect enabled or disabled
    void setEnabled(bool enable);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::size_t m_numberOfClouds { 0 };
    jt::Vector2f m_screnArea { 0.0f, 0.0f };
    jt::Vector2f m_margin { 0.0f, 0.0f };

    bool m_enabled { true };

    std::vector<std::shared_ptr<jt::Animation>> m_clouds;
};

} // namespace jt

#endif // FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HORIZONTAL_HPP
