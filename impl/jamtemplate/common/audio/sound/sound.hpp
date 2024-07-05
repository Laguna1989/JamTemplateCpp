#ifndef JAMTEMPLATE_SOUND_HPP
#define JAMTEMPLATE_SOUND_HPP

#include <audio/sound/sound_base.hpp>
#include <counted_object.hpp>
#include <string>

namespace jt {

class Sound : public SoundBase, public CountedObj<Sound> {
public:
    Sound(std::string const& fileName);

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

private:
    std::string m_fileName;
};

} // namespace jt
#endif // JAMTEMPLATE_SOUND_HPP
