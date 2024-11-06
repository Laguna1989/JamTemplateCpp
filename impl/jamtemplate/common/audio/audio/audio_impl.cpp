#include "audio_impl.hpp"
#include <audio/sound/sound.hpp>
#include <random/random.hpp>
#include <tracy/Tracy.hpp>
#include <fmod_errors.h>
#include <sstream>

namespace {
FMOD_STUDIO_INITFLAGS getStudioInitFlags()
{
#if JT_ENABLE_WEB
    return FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE;
#else
    return FMOD_STUDIO_INIT_LIVEUPDATE;
#endif
}
} // namespace

void jt::checkResult(FMOD_RESULT result)
{
    if (result == FMOD_OK) {
        return;
    }

    std::ostringstream oss;
    oss << "FMod Failed: (" << result << ") - " << FMOD_ErrorString(result);
    throw std::logic_error { oss.str() };
}

jt::AudioImpl::AudioImpl()
{
    ZoneScopedN("jt::AudioImpl::AudioImpl");
    checkResult(FMOD::Studio::System::create(&m_studioSystem));
    checkResult(m_studioSystem->initialize(128, getStudioInitFlags(), FMOD_INIT_NORMAL, nullptr));

    FMOD::Studio::Bank* stringBank;
    checkResult(m_studioSystem->loadBankFile(
        "assets/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringBank));

    FMOD::Studio::Bank* masterBank;
    checkResult(m_studioSystem->loadBankFile(
        "assets/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));

    if (m_studioSystem == nullptr)
        throw std::logic_error { "FMOD studio system was not properly instantiated" };
}

jt::AudioImpl::~AudioImpl()
{
    // Do not use logger here anymore
    if (m_studioSystem)
        m_studioSystem->release();
    m_studioSystem = nullptr;
}

void jt::AudioImpl::update(float /*elapsed*/) { m_studioSystem->update(); }

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::addTemporarySound(std::string const& eventPath)
{
    FMOD::Studio::EventDescription* eventDescription;
    m_studioSystem->getEvent(eventPath.c_str(), &eventDescription);

    FMOD::Studio::EventInstance* eventInstance;
    eventDescription->createInstance(&eventInstance);

    eventInstance->start();
    return std::make_shared<jt::Sound>(eventInstance);
}

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::addPermanentSound(
    std::string const& identifier, std::string const& eventPath)
{
    FMOD::Studio::EventDescription* eventDescription;
    checkResult(m_studioSystem->getEvent(eventPath.c_str(), &eventDescription));

    if (eventDescription == nullptr) {
        return nullptr;
    }
    FMOD::Studio::EventInstance* eventInstance;
    eventDescription->createInstance(&eventInstance);

    eventInstance->start();
    permanentSounds[identifier] = eventInstance;
    return std::make_shared<jt::Sound>(eventInstance);
}

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::getPermanentSound(std::string const& identifier)
{
    if (permanentSounds.contains(identifier))
        return std::make_shared<jt::Sound>(permanentSounds[identifier]);

    return nullptr;
}

void jt::AudioImpl::setGroupVolume(std::string const& groupPath, float newVolume)
{
    FMOD::Studio::Bus* bus { nullptr };
    checkResult(m_studioSystem->getBus(groupPath.c_str(), &bus));
    if (bus == nullptr) {
        return;
    }
    checkResult(bus->setVolume(newVolume));
}

float jt::AudioImpl::getGroupVolume(std::string const& groupPath)
{
    FMOD::Studio::Bus* bus { nullptr };
    checkResult(m_studioSystem->getBus(groupPath.c_str(), &bus));
    if (bus == nullptr) {
        return 0.0f;
    }
    float volume { 0.0f };
    checkResult(bus->getVolume(&volume));
    return volume;
}
