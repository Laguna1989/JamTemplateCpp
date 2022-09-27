#ifndef JAMTEMPLATE_SOUND_COMPONENT_INTERFACE_HPP
#define JAMTEMPLATE_SOUND_COMPONENT_INTERFACE_HPP

class SoundComponentInterface {
public:
    enum class SoundId { SoundID };
    virtual ~SoundComponentInterface() = default;
    virtual void play(SoundId sound) = 0;

    virtual bool isPlaying(SoundId sound) = 0;
};

#endif // JAMTEMPLATE_SOUND_COMPONENT_INTERFACE_HPP
