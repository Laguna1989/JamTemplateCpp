﻿#ifndef GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD

#include <cassert>
#include <functional>
#include <memory>

namespace jt {

class TweenBase {
public:
    using Sptr = std::shared_ptr<TweenBase>;

    using OnCompleteCallbackType = std::function<void(void)>;

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
        // if (m_age < m_startDelay) return;
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

    void setAgePercentConversion(std::function<float(float)> func)
    {
        m_agePercentConversion = func;
    }

protected:
    float m_totalTime { 0.0f };

private:
    int m_skipFrames { 0 };
    float m_age { 0.0f };
    float m_startDelay {};
    bool m_alive { true };
    bool m_repeat { false };

    std::function<float(float)> m_agePercentConversion { nullptr };

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

template <class T>
class Tween : public TweenBase {
public:
    using OnUpdateCallbackType = std::function<bool(std::shared_ptr<T>, float)>;
    Tween(std::weak_ptr<T> obj, OnUpdateCallbackType cb, float totalTime)
        : m_obj { obj }
        , m_tweenCallback { cb }
    {
        TweenBase::m_totalTime = totalTime;
    }

protected:
private:
    std::weak_ptr<T> m_obj;

    // update callback function. If the callback returns false, the tween shall be finished.
    OnUpdateCallbackType m_tweenCallback;
    void doUpdate(float /*elapsed*/) override
    {
        std::shared_ptr<T> sptr = nullptr;
        getObject(sptr);
        if (sptr == nullptr) {
            return;
        }
        if (!m_tweenCallback(sptr, getConvertedAgePercent(getAgePercent()))) {
            finish();
        }
    }

    void getObject(std::shared_ptr<T>& obj)
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
