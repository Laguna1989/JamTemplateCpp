#include "tilemap_manager_tileson_impl.hpp"
#include <iostream>

namespace jt {
std::unique_ptr<tson::Map>& TilemapManagerTilesonImpl::getMap(std::string const& fileName)
{
    if (m_maps.count(fileName) == 0) {
        tson::Tileson parser;

        auto map = parser.parse(fileName);
        if (map->getStatus() != tson::ParseStatus::OK) {
            std::cerr << "tilemap json could not be parsed.\n";
            throw std::invalid_argument { "tilemap json could not be parsed." };
        }
        m_maps[fileName] = std::move(map);
    }

    return m_maps.at(fileName);
}
} // namespace jt
