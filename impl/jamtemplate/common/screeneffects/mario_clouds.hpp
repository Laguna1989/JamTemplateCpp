#ifndef FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HPP
#define FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HPP

#include <animation.hpp>
#include <game_object.hpp>

// TODO add to demo
class MarioClouds : public jt::GameObject {
public:
    MarioClouds(jt::Vector2f const& mapSize, jt::Vector2f const& margin);

    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_mapSize;
    jt::Vector2f m_margin;

    std::vector<std::shared_ptr<jt::Animation>> m_clouds;
};

#endif // FRUITLOVINMONKEYPIRATES_MARIO_CLOUDS_HPP
