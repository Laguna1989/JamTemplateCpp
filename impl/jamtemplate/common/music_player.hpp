#ifndef GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD

#include "music_player_interface.hpp"
#include "oalpp/sound.hpp"
#include "oalpp/sound_data.hpp"
#include <memory>
#include <optional>

namespace jt {

class MusicPlayer : public jt::MusicPlayerInterface {
public:
    explicit MusicPlayer(oalpp::SoundContext const& ctx);
    virtual void playMusic(std::string const& fileName) override;
    virtual void stopMusic() override;
    // range: 0.0f to 100.0f
    virtual void setMusicVolume(float v) override;
    virtual float getMusicVolume() override;
    virtual std::string getMusicFilePath() override;
    void update() override;

private:
    std::string m_musicFileName;
    // can be optional, once oalpp sound supports copy construction
    std::shared_ptr<oalpp::Sound> m_music;
    std::optional<oalpp::SoundData> m_buffer;

    oalpp::SoundContext const& m_ctx;
};

} // namespace jt
#endif
