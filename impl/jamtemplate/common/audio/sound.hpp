#ifndef JAMTEMPLATE_SOUND_HPP
#define JAMTEMPLATE_SOUND_HPP

#include <audio/sound_base.hpp>
#include <counted_object.hpp>
#include <oalpp/sound.hpp>
#include <oalpp/sound_data.hpp>
#include <string>

namespace jt {

class Sound : public SoundBase, public CountedObj<Sound> {
public:
    explicit Sound(std::string const& fileName);

    void update() override;

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;

    float getPosition() const override;

    int getSampleRate() const override;

private:
    oalpp::SoundData m_buffer;
    oalpp::Sound m_sound;
    std::string m_fileName;
};

} // namespace jt
#endif // JAMTEMPLATE_SOUND_HPP
