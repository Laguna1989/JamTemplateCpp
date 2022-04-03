#ifndef MYAWESOMEGAME_SOUND_COMPONENT_INTERFACE_HPP
#define MYAWESOMEGAME_SOUND_COMPONENT_INTERFACE_HPP

class SoundComponentInterface {
public:
    enum class SoundId { SoundID };
    virtual ~SoundComponentInterface() = default;
    virtual void play(SoundId sound) = 0;

    virtual bool isPlaying(SoundId sound) = 0;
};

#endif // MYAWESOMEGAME_SOUND_COMPONENT_INTERFACE_HPP
