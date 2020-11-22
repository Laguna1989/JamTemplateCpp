#ifndef GAMEINTERFACE_HPP_GUARD
#define GAMEINTERFACE_HPP_GUARD

#include "GameObject.hpp"
#include <memory>
#include <string>

namespace JamTemplate {

// fwd decls
class GameState;

class GameInterface {
public:
    virtual void runGame(std::shared_ptr<GameState> InitialState) = 0;
};

class AgnosticGame {
};

} // namespace JamTemplate
#endif
