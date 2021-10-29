#ifndef GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <vector>

namespace jt {

class TweenBase {
public:
    using Sptr = std::shared_ptr<TweenBase>;
    using OnCompleteCallbackType = std::function<void(void)>;

    // This will cause a compile error if a lambda is passed, because lambdas cannot be
    // converted to function pointers. However, it is safe to assume that the age-percent conversion
    // will not need to capture anything as it is just a simple conversion function from float to
    // float. If this causes issues, just change the using alias to use std::function<float(float)>
    using AgePercentConversionFunctionType = std::add_pointer<float(float)>::type;

    TweenBase() = default;
    virtual ~TweenBase() = default;

    /// TweenBase should never be copied!
    TweenBase(TweenBase const&) = delete;
    TweenBase& operator=(TweenBase const&) = delete;

    TweenBase(TweenBase&&) = default;
    TweenBase& operator=(TweenBase&&) = default;

    void cancel() { kill(); }

    void finish()
    {
        handleCompleteCallbacks();
        if (m_repeat) {
            m_age = 0;
        } else {
            kill();
        }
    }

    void update(float elapsed)
    {
        if (m_skipFrames > 0) {
            m_skipFrames--;
            return;
        }
        m_age += elapsed;
        doUpdate(elapsed);
    }
    bool isAlive() { return m_alive; }
    void kill() { m_alive = false; }
    void setStartDelay(float delay) { m_startDelay = delay; }
    float getStartDelay() const { return m_startDelay; }
    void addCompleteCallback(OnCompleteCallbackType cb) { m_completeCallbacks.push_back(cb); }

    void setSkipFrames(int skf = 1) { m_skipFrames = skf; }
    int getSkipFrames() const { return m_skipFrames; }

    void setRepeat(bool repeat) { m_repeat = repeat; }
    bool getRepeat() const { return m_repeat; }

    float getAge() const { return m_age - m_startDelay; }
    float getAgePercent() const { return getAge() / m_totalTime; }
    float getConvertedAgePercent(float age) const
    {
        if (m_agePercentConversion == nullptr) {
            return age;
        }
        return m_agePercentConversion(age);
    }

    void setAgePercentConversion(AgePercentConversionFunctionType func)
    {
        m_agePercentConversion = func;
    }

protected:
    float m_totalTime { 0.0f };

private:
    int m_skipFrames { 0 };
    float m_age { 0.0f };
    float m_startDelay { 0.0f };
    bool m_alive { true };
    bool m_repeat { false };

    AgePercentConversionFunctionType m_agePercentConversion { nullptr };

    std::vector<OnCompleteCallbackType> m_completeCallbacks;

    virtual void doUpdate(float elapsed) = 0;
    void handleCompleteCallbacks()
    {
        for (auto& cb : m_completeCallbacks) {
            assert(cb);
            cb();
        }
    }
};

class Tween : public TweenBase {
public:
    using OnUpdateCallbackType = std::function<void(std::shared_ptr<DrawableInterface>, float)>;
    Tween(std::weak_ptr<DrawableInterface> obj, OnUpdateCallbackType cb, float totalTime)
        : m_obj { obj }
        , m_tweenCallback { cb }
    {
        TweenBase::m_totalTime = totalTime;
    }

protected:
private:
    std::weak_ptr<DrawableInterface> m_obj;

    // update callback function. If the callback returns false, the tween shall be finished.
    OnUpdateCallbackType m_tweenCallback;
    void doUpdate(float /*elapsed*/) override
    {
        if (getAgePercent() >= 1.0f) {
            finish();
        }
        std::shared_ptr<DrawableInterface> sptr = nullptr;
        getObject(sptr);
        if (sptr == nullptr) {
            return;
        }
        m_tweenCallback(sptr, getConvertedAgePercent(getAgePercent()));
    }

    void getObject(std::shared_ptr<DrawableInterface>& obj)
    {
        if (m_obj.expired()) {
            finish();
            obj = nullptr;
            return;
        }
        obj = m_obj.lock();
    }
};

} // namespace jt

#endif
