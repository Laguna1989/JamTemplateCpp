#ifndef DEMO_SCENE_TILEMAP_COLLISIONS_HPP
#define DEMO_SCENE_TILEMAP_COLLISIONS_HPP

#include <game_object.hpp>
#include <rect.hpp>
#include <shape.hpp>
#include <text.hpp>
#include <tilemap/tile_layer.hpp>
#include <memory>
#include <vector>

/// Shows the collision rects loaded from a tilemap, once per blocked tile and once merged by
/// jt::TilemapCollisions::refineColliders().
class SceneTilemapCollisions : public jt::GameObject {
public:
    std::string getName() const override;

private:
    struct ColliderSet {
        std::vector<jt::Rectf> rects;
        std::vector<std::shared_ptr<jt::Shape>> shapes;
        std::vector<jt::Color> colors;
    };

    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayer { nullptr };
    ColliderSet m_rawColliders {};
    ColliderSet m_refinedColliders {};
    bool m_showRefined { true };
    std::shared_ptr<jt::Text> m_info { nullptr };

    void doCreate() override;
    void doUpdate(float elapsed) override;
    void doDraw() const override;

    ColliderSet createColliderSet(std::vector<jt::Rectf> const& rects) const;
    ColliderSet& activeColliders();
    ColliderSet const& activeColliders() const;
};

#endif // DEMO_SCENE_TILEMAP_COLLISIONS_HPP
