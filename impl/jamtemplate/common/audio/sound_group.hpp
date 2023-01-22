#ifndef JAMTEMPLATE_SOUNDGROUP_HPP
#define JAMTEMPLATE_SOUNDGROUP_HPP

#include <audio/sound_interface.hpp>
#include <memory>
#include <string>
#include <vector>

namespace oalpp {
class SoundContext;
}

namespace jt {
class SoundGroup : public SoundInterface {
public:
    /// Constructor
    SoundGroup() = default;

    /// Constructor for convenience
    /// \param sounds list of filepaths to load
    explicit SoundGroup(std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds);

    std::size_t size() const;

    void add(std::shared_ptr<SoundInterface> sound);

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    // not implemented correctly
    float getDuration() const override;
    // not implemented correctly
    float getPosition() const override;
    void update() override;
    void setBlend(float blend) override;
    float getBlend() const override;

    int getSampleRate() const override;

    void setVolumeProvider(GroupVolumeGetterInterface& provider) override;

    void setVolumeGroup(std::string const& volumeGroupName) override;

private:
    std::vector<std::shared_ptr<SoundInterface>> m_sounds {};
};
} // namespace jt
#endif
