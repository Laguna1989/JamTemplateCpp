#include "tilemap_cache.hpp"
#include <iostream>

std::shared_ptr<tson::Map> jt::TilemapCache::getMap(std::string const& fileName) const
{
    if (m_maps.count(fileName) == 0) {
        tson::Tileson parser;

        auto map = parser.parse(fileName);
        if (map->getStatus() != tson::ParseStatus::OK) {
            std::cerr << "tilemap json could not be parsed: '" << fileName << std::endl;
            throw std::invalid_argument { "tilemap json could not be parsed." };
        }
        m_maps[fileName] = std::move(map);
    }

    return m_maps.at(fileName);
}
