#ifndef JAMTEMPLATE_MOCK_SOUND_HPP
#define JAMTEMPLATE_MOCK_SOUND_HPP

#include <audio/sound/sound_interface.hpp>
#include <gmock/gmock.h>

class MockSound : public jt::SoundInterface {
public:
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(bool, isPlaying, (), (const, override));
    MOCK_METHOD(void, play, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(float, getVolume, (), (const, override));
    MOCK_METHOD(void, setVolume, (float), (override));
    MOCK_METHOD(float, getFinalVolume, (), (const, override));
    MOCK_METHOD(void, setPitch, (float), (override));
    MOCK_METHOD(float, getPitch, (), (const, override));
    MOCK_METHOD(void, setLoop, (bool), (override));
    MOCK_METHOD(bool, getLoop, (), (override));
    MOCK_METHOD(float, getDuration, (), (const, override));
    MOCK_METHOD(float, getPosition, (), (const, override));
    MOCK_METHOD(void, setBlend, (float), (override));
    MOCK_METHOD(float, getBlend, (), (const, override));
    MOCK_METHOD(int, getSampleRate, (), (const, override));
    MOCK_METHOD(void, setVolumeProvider, (jt::GroupVolumeGetterInterface&), (override));
    MOCK_METHOD(void, setVolumeGroup, (std::string const&), (override));
};

#endif // JAMTEMPLATE_MOCK_SOUND_HPP
