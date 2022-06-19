#ifndef JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP
#define JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP

namespace jt {
class TweenInterface {
public:
    virtual ~TweenInterface() = default;

    virtual void update(float elapsed) = 0;
    virtual bool isAlive() const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_GAME_OBJECT_INTERFACE_HPP
