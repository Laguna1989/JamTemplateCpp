#include "tilemap_cache.hpp"
#include <tracy/Tracy.hpp>
#include <iostream>

std::shared_ptr<tson::Map> jt::TilemapCache::get(std::string const& fileName) const
{
    ZoneScopedN("jt::TilemapCache::get");
    if (!m_maps.contains(fileName)) {
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

std::size_t jt::TilemapCache::getNumberOfMaps() const { return m_maps.size(); }
