#ifndef GUARD_JAMTEMPLATE_AFX_IMPL_HPP
#define GUARD_JAMTEMPLATE_AFX_IMPL_HPP

#include "afx_interface.hpp"
#include "oalpp/sound_context.hpp"
#include <vector>

namespace jt {
class AfxImpl : public AfxInterface {
public:
    std::shared_ptr<SoundInterface> createSound(std::string const& fileName) override;
    void removeSound(std::shared_ptr<SoundInterface> snd) override;
    void update() override;

private:
    // TODO should only store weak pointers
    std::vector<std::shared_ptr<SoundInterface>> m_sounds;
    oalpp::SoundContext m_context;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AFX_IMPL_HPP
