#ifndef GUARD_JAMTEMPLATE_AFX_NULL_HPP
#define GUARD_JAMTEMPLATE_AFX_NULL_HPP

#include "afx_interface.hpp"

namespace jt {
class AfxNull : public AfxInterface {
public:
    std::shared_ptr<SoundInterface> createSound(std::string const& fileName) override;
    void removeSound(std::shared_ptr<SoundInterface> snd) override;
    void update() override;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AFX_NULL_HPP
