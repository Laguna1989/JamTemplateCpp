#include "sound.hpp"
#include <stdexcept>

jt::Sound::Sound(std::string const& fileName)
    : m_fileName { fileName }
{
}

bool jt::Sound::isPlaying() const
{
    // TODO(Simon)
    return false;
}

void jt::Sound::play()
{
    // TODO(Simon)
}

void jt::Sound::stop()
{
    // TODO(Simon)
}

void jt::Sound::pause()
{
    // TODO(Simon)
}
