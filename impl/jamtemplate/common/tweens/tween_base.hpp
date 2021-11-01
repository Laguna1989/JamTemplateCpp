#ifndef GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include <functional>
#include <memory>
#include <vector>

namespace jt {

class Tween {
public:
    using Sptr = std::shared_ptr<Tween>;
    using OnCompleteCallbackType = std::function<void(void)>;

    // Using a raw function pointer will cause a compile error if a lambda is passed, because
    // lambdas cannot be converted to function pointers. However, it is safe to assume that the
    // age-percent conversion will not need to capture anything as it is just a simple conversion
    // function from float to float. If this causes issues, just change the using alias to use
    // std::function<float(float)>
    using AgePercentConversionFunctionType = std::add_pointer<float(float)>::type;

    /// Constructor
    ///
    /// \param obj the object to be tweened
    /// \param cb the function that does the tweening
    /// \param tweenDurationInSeconds the total time for the tween in seconds
    Tween(std::weak_ptr<DrawableInterface> obj, float tweenDurationInSeconds);

    /// Destructor
    virtual ~Tween() = default;

    // Tween should never be copied!
    Tween(Tween const&) = delete;
    Tween& operator=(Tween const&) = delete;

    Tween(Tween&&) = default;
    Tween& operator=(Tween&&) = default;

    /// Cancel the tween
    void cancel();

    /// Finish the tween
    /// Will call handleCompleteCallback
    /// If tween is set to repeat, this will trigger the restart
    void finish();

    /// Update the tween
    void update(float elapsed);

    /// Check if tween is alive
    /// \return true if alive, false otherwise
    bool isAlive();

    /// Kill the tween
    void kill();

    /// Set start delay
    /// \param startDelayInSeconds start delay in seconds
    void setStartDelay(float startDelayInSeconds);

    /// Get start delay
    /// \return start delay in seconds
    float getStartDelay() const;

    /// Add a callback that is invoked when the tween is complete
    /// \param cb the callback
    void addCompleteCallback(OnCompleteCallbackType cb);

    /// Set skipframes
    /// \param framesToSkip the amount of frames to skip
    void setSkipFrames(int framesToSkip = 1);

    /// Get skipframes
    /// \return the amount of frames to skip
    int getSkipFrames() const;

    /// Set the tween to repeat
    /// \param repeat how often the tween should repeat
    void setRepeat(bool repeat);

    /// Get the number of remaining repeats
    /// \return how often the tween will repeat
    bool getRepeat() const;

    /// Get age
    /// \return the time since the tween started
    float getAge() const;

    /// Get age percent
    /// \return in 0 - 1
    float getAgePercent() const;

    /// Get age percent converted
    /// \param age the age
    /// \return the updated converted age percent, in range 0 - 1
    float getConvertedAgePercent(float age) const;

    /// Set conversion function for age percent (e.g. cubic)
    /// \param func the conversion function
    void setAgePercentConversion(AgePercentConversionFunctionType func);

private:
    int m_skipFrames { 0 };
    float m_totalTime;
    float m_age { 0.0f };
    float m_startDelayInSeconds { 0.0f };
    bool m_alive { true };
    bool m_repeat { false };
    std::weak_ptr<DrawableInterface> m_obj;

    /// Function that does the actual tweening. Needs to be overwritten by derived classes
    /// \param sptr the object to tween
    /// \param agePercent value between 0 and 1 which indicates the percentage of the tween
    /// progression.
    virtual void doUpdateObject(
        std::shared_ptr<DrawableInterface> const& sptr, float agePercent) const;

    AgePercentConversionFunctionType m_agePercentConversion { nullptr };

    std::vector<OnCompleteCallbackType> m_completeCallbacks {};

    void doUpdate(float /*elapsed*/);

    void handleCompleteCallbacks();
};

} // namespace jt

#endif
