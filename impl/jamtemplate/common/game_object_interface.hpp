#ifndef JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP
#define JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP

#include <string>

namespace jt {
class GameObjectInterface {
public:
    virtual ~GameObjectInterface() = default;

    virtual void create() = 0;
    virtual void update(float elapsed) = 0;
    virtual void draw() const = 0;

    virtual void kill() = 0;
    virtual bool isAlive() const = 0;
    virtual void destroy() = 0;

    virtual std::string getName() const = 0;
};

} // namespace jt

#endif // JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP
