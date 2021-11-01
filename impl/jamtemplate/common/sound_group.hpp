#ifndef JAMTEMPLATE_SOUNDGROUP_HPP_GUARD
#define JAMTEMPLATE_SOUNDGROUP_HPP_GUARD

#include "sound_base.hpp"
#include <memory>
#include <vector>

namespace jt {
class SoundGroup : public SoundBase {
public:
    /// Constructor
    SoundGroup() = default;

    /// Constructor
    /// \param sounds list of filepaths to load
    explicit SoundGroup(std::vector<std::string> const& sounds);

private:
    std::vector<std::shared_ptr<SoundBase>> m_sounds {};

    virtual void doLoad(std::string const& fileName) override;
    virtual bool doIsPlaying() const override;

    virtual void doPlay() override;
    virtual void doStop() override;

    virtual float doGetVolume() const override;
    virtual void doSetVolume(float newVolume) override;

    virtual void doSetLoop(bool doLoop) override;
    virtual bool doGetLoop(void) override;

    // not implemented correctly
    virtual float doGetDuration() const override;
    // not implemented correctly
    virtual float doGetPosition() const override;
};
} // namespace jt
#endif
