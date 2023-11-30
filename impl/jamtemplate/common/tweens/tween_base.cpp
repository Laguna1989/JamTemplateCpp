#include "tween_base.hpp"
#include <cassert>

jt::Tween::Tween(std::weak_ptr<DrawableInterface> obj, float tweenDurationInSeconds)
    : m_totalTime { tweenDurationInSeconds }
    , m_obj { obj }
{
}

void jt::Tween::cancel() { kill(); }

void jt::Tween::finish()
{
    handleCompleteCallbacks();
    if (m_repeat) {
        m_age = 0;
    } else {
        kill();
    }
}

void jt::Tween::update(float elapsed)
{
    if (m_skipTicks > 0) {
        m_skipTicks--;
        return;
    }
    m_age += elapsed;
    m_agePercent = (m_age - m_startDelayInSeconds) / m_totalTime;
    doUpdate(elapsed);
}

bool jt::Tween::isAlive() const { return m_alive; }

void jt::Tween::kill() { m_alive = false; }

void jt::Tween::setStartDelay(float startDelayInSeconds)
{
    m_startDelayInSeconds = startDelayInSeconds;
}

float jt::Tween::getStartDelay() const { return m_startDelayInSeconds; }

void jt::Tween::addCompleteCallback(jt::Tween::OnCompleteCallbackType cb)
{
    m_completeCallbacks.push_back(cb);
}

void jt::Tween::setSkipTicks(int framesToSkip) { m_skipTicks = framesToSkip; }

int jt::Tween::getSkipFrames() const { return m_skipTicks; }

void jt::Tween::setRepeat(bool repeat) { m_repeat = repeat; }

bool jt::Tween::getRepeat() const { return m_repeat; }

float jt::Tween::getAge() const { return m_age - m_startDelayInSeconds; }

float jt::Tween::getAgePercent() const { return m_agePercent; }

float jt::Tween::getConvertedAgePercent(float agePercent) const
{
    if (m_agePercentConversion == nullptr) {
        return agePercent;
    }
    return m_agePercentConversion(agePercent);
}

void jt::Tween::setAgePercentConversion(jt::Tween::AgePercentConversionFunctionType func)
{
    m_agePercentConversion = func;
}

void jt::Tween::doUpdate(float)
{
    if (getAgePercent() >= 1.0f) {
        finish();
    }
    auto obj = m_obj.lock();
    if (!obj) [[unlikely]] {
        finish();
        return;
    }
    doUpdateObject(obj, getConvertedAgePercent(getAgePercent()));
}

void jt::Tween::handleCompleteCallbacks()
{
    for (auto& cb : m_completeCallbacks) {
        assert(cb);
        cb();
    }
}

void jt::Tween::doUpdateObject(
    std::shared_ptr<DrawableInterface> const& /*sptr*/, float /*agePercent*/) const
{
}
