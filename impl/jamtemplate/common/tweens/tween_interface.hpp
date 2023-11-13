#ifndef JAMTEMPLATE_TWEEN_INTERFACE_HPP
#define JAMTEMPLATE_TWEEN_INTERFACE_HPP

namespace jt {
class TweenInterface {
public:
    /// update the tween
    /// \param elapsed elapsed time in seconds
    virtual void update(float elapsed) = 0;

    /// check if the tween is alive
    /// \return true if alive, false otherwise
    virtual bool isAlive() const = 0;

    /// Destructor
    virtual ~TweenInterface() = default;

    // no copy, no move. Avoid slicing.
    TweenInterface(TweenInterface const&) = delete;
    TweenInterface(TweenInterface&&) = delete;
    TweenInterface& operator=(TweenInterface const&) = delete;
    TweenInterface& operator=(TweenInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    TweenInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_TWEEN_INTERFACE_HPP
