#include "afx_null.hpp"
#include "sound_null.hpp"
namespace jt {
std::shared_ptr<SoundInterface> AfxNull::createSound(std::string const& fileName)
{
    return std::make_shared<SoundNull>();
}
void AfxNull::removeSound(std::shared_ptr<SoundInterface> snd) { }

void AfxNull::update() { }
} // namespace jt
