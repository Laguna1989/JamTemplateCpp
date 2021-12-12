#ifndef GUARD_JAMTEMPLATE_TILEMAPMANAGERINTERFACE_HPP
#define GUARD_JAMTEMPLATE_TILEMAPMANAGERINTERFACE_HPP

#include "tileson.h"

namespace jt {
class TilemapManagerInterface {
public:
    virtual ~TilemapManagerInterface() = default;

    // TODO think about creating an jt abstraction for this
    virtual std::unique_ptr<tson::Map>& getMap(std::string const& fileName) = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_TILEMAPMANAGERINTERFACE_HPP
