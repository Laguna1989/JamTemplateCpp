#include "afx_impl.hpp"
#include "sound.hpp"

namespace jt {
std::shared_ptr<SoundInterface> AfxImpl::createSound(std::string const& fileName)
{
    auto snd = std::make_shared<Sound>(fileName, m_context);
    m_sounds.push_back(snd);
    return snd;
}

void AfxImpl::removeSound(std::shared_ptr<SoundInterface> snd)
{
    // TODO
}

void AfxImpl::update()
{
    for (auto const& snd : m_sounds) {
        snd->update();
    }
}
} // namespace jt
