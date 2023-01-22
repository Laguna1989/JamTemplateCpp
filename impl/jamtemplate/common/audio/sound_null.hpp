#ifndef JAMTEMPLATE_SOUND_NULL_HPP
#define JAMTEMPLATE_SOUND_NULL_HPP

#include <audio/sound_interface.hpp>

namespace jt {

class SoundNull : public SoundInterface {
public:
    void update() override;

    bool isPlaying() const override;
    void play() override;
    void pause() override;
    void stop() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;
    float getPosition() const override;

    void setBlend(float blend) override;
    float getBlend() const override;

    int getSampleRate() const override;
    void setVolumeProvider(GroupVolumeGetterInterface& provider) override;
    void setVolumeGroup(std::string const& string) override;
};
} // namespace jt

#endif // JAMTEMPLATE_SOUND_NULL_HPP
