#ifndef JAMTEMPLATE_TWEEN_INTERFACE_HPP
#define JAMTEMPLATE_TWEEN_INTERFACE_HPP

namespace jt {
class TweenInterface {
public:
    virtual ~TweenInterface() = default;

    virtual void update(float elapsed) = 0;
    virtual bool isAlive() const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_TWEEN_INTERFACE_HPP
