#ifndef JAMTEMPLATE_LEVEL_HPP
#define JAMTEMPLATE_LEVEL_HPP

#include "box2dwrapper/box2d_object.hpp"
#include "tilemap/tile_layer.hpp"
#include "tilemap/tileson_loader.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_object.hpp>
#include <shape.hpp>

class Level : public jt::GameObject {
public:
    Level(std::string const& fileName, std::weak_ptr<jt::Box2DWorldInterface> world);
    jt::Vector2f getPlayerStart() const;

    bool checkIfPlayerIsInKillbox(jt::Vector2f const& playerPosition) const;

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::shared_ptr<jt::Shape> m_background;
    std::string m_fileName { "" };
    std::weak_ptr<jt::Box2DWorldInterface> m_world;

    std::vector<std::shared_ptr<jt::Box2DObject>> m_colliders {};
    std::shared_ptr<jt::tilemap::TileLayer> m_tileLayerGround { nullptr };
    jt::Vector2f m_playerStart { 0.0f, 0.0f };

    std::vector<jt::tilemap::InfoRect> m_killboxes;
    void loadLevelSettings(jt::tilemap::TilesonLoader& loader);
    void loadLevelTileLayer(jt::tilemap::TilesonLoader& loader);
    void loadLevelCollisions(jt::tilemap::TilesonLoader& loader);
    void loadLevelKillboxes(jt::tilemap::TilesonLoader& loader);
};

#endif // JAMTEMPLATE_LEVEL_HPP
