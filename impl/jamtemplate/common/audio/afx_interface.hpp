#ifndef GUARD_JAMTEMPLATE_AFX_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_AFX_INTERFACE_HPP

#include "sound_interface.hpp"
#include <memory>
#include <string>

namespace jt {

class AfxInterface {
public:
    virtual ~AfxInterface() = default;
    virtual std::shared_ptr<SoundInterface> createSound(std::string const& fileName) = 0;

    virtual void removeSound(std::shared_ptr<SoundInterface> snd) = 0;

    virtual void update() = 0;

    // TODO add playMusic function

    // TODO add group functionality
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_AFX_INTERFACE_HPP
