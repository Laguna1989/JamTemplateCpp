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
    if (m_skipFrames > 0) {
        m_skipFrames--;
        return;
    }
    m_age += elapsed;
    doUpdate(elapsed);
}

bool jt::Tween::isAlive() { return m_alive; }

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

void jt::Tween::setSkipFrames(int framesToSkip) { m_skipFrames = framesToSkip; }

int jt::Tween::getSkipFrames() const { return m_skipFrames; }

void jt::Tween::setRepeat(bool repeat) { m_repeat = repeat; }

bool jt::Tween::getRepeat() const { return m_repeat; }

float jt::Tween::getAge() const { return m_age - m_startDelayInSeconds; }

float jt::Tween::getAgePercent() const { return getAge() / m_totalTime; }

float jt::Tween::getConvertedAgePercent(float age) const
{
    if (m_agePercentConversion == nullptr) {
        return age;
    }
    return m_agePercentConversion(age);
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
    if (m_obj.expired()) {
        finish();
        return;
    }
    doUpdateObject(m_obj.lock(), getConvertedAgePercent(getAgePercent()));
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
