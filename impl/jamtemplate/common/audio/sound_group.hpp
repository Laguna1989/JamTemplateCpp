#ifndef JAMTEMPLATE_SOUNDGROUP_HPP_GUARD
#define JAMTEMPLATE_SOUNDGROUP_HPP_GUARD

#include "sound_interface.hpp"
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

    /// Constructor
    /// \param sounds list of filepaths to load
    explicit SoundGroup(std::vector<std::string> const& sounds, oalpp::SoundContext const& ctx);

private:
    std::vector<std::shared_ptr<SoundInterface>> m_sounds {};

    void addSound(std::string const& fileName, oalpp::SoundContext const& ctx);
    bool isPlaying() const override;

    void play() override;
    void stop() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    // not implemented correctly
    float getDuration() const override;
    // not implemented correctly
    float getPosition() const override;
};
} // namespace jt
#endif
