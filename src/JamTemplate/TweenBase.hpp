#ifndef JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEENBASE_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

namespace JamTemplate {
class TweenBase {
public:
    using Sptr = std::shared_ptr<TweenBase>;

    using CallbackType = std::function<void(void)>;

    TweenBase() = default;
    virtual ~TweenBase() = default;

    /// TweenBase should never be copied!
    TweenBase(TweenBase const&) = delete;
    TweenBase& operator=(TweenBase const&) = delete;

    TweenBase(TweenBase&&) = default;
    TweenBase& operator=(TweenBase&&) = default;

    void cancel()
    {
        kill();
    }

    void finish()
    {
        handleCompleteCallbacks();
        kill();
    }

    void update(float elapsed)
    {
        if (m_skipFrames > 0) {
            m_skipFrames--;
            return;
        }
        m_age += elapsed;
        //if (m_age < m_startDelay) return;
        doUpdate(elapsed);
    }
    bool isAlive()
    {
        return m_alive;
    }
    void kill()
    {
        m_alive = false;
    }
    void setStartDelay(float delay)
    {
        m_startDelay = delay;
    }
    float getStartDelay() const
    {
        return m_startDelay;
    }
    void addCompleteCallback(CallbackType cb)
    {
        m_completeCallbacks.push_back(cb);
    }

    void setSkipFrames(int skf = 1)
    {
        m_skipFrames = skf;
    }
    int getSkipFrames() const
    {
        return m_skipFrames;
    }

protected:
    float getAge() const { return m_age - m_startDelay; }

private:
    int m_skipFrames { 0 };
    float m_age { 0.0f };
    float m_startDelay {};
    bool m_alive { true };

    std::vector<CallbackType> m_completeCallbacks;

    virtual void doUpdate(float elapsed) = 0;
    void handleCompleteCallbacks()
    {
        for (auto& cb : m_completeCallbacks) {
            cb();
        }
    }
};

template <class T>
class Tween : public TweenBase {
public:
    using Callback_type = std::function<bool(std::shared_ptr<T>, float)>;
    Tween(std::weak_ptr<T> obj, Callback_type cb)
        : m_obj { obj }
        , m_tweenCallback { cb }
    {
    }

protected:
private:
    std::weak_ptr<T> m_obj;

    // callback function. If the callback returns false, the tween shall be finished.
    Callback_type m_tweenCallback;
    void doUpdate(float /*elapsed*/) override
    {
        std::shared_ptr<T> sptr = nullptr;
        getObject(sptr);
        if (sptr == nullptr) {
            return;
        }
        if (!m_tweenCallback(sptr, getAge())) {
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
} // namespace JamTemplate

#endif
