#ifndef GUARD_JAMTEMPLATE_TILESON_LOADER_HPP
#define GUARD_JAMTEMPLATE_TILESON_LOADER_HPP

#include "info_rect.hpp"
#include "texture_manager_interface.hpp"
#include "tile_node.hpp"
#include "tilemap_manager_interface.hpp"
#include <memory>

namespace jt {
namespace tilemap {

class TilesonLoader {
public:
    TilesonLoader(
        std::shared_ptr<TilemapManagerInterface> tilemapManager, std::string const& fileName);

    std::vector<InfoRect> loadObjectsFromLayer(std::string const& layerName);

    std::vector<std::shared_ptr<TileNode>> LoadNodesFromLayer(
        std::string const& layerName, std::shared_ptr<jt::TextureManagerInterface> textureManager);

private:
    std::shared_ptr<TilemapManagerInterface> m_tilemapManager;
    std::string m_fileName;
};

} // namespace tilemap
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILESON_LOADER_HPP
