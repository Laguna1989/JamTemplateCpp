#pragma once

#include <game_object.hpp>
#include <string>

namespace jt {

/// Class to display license and build info
class LicenseInfo : public GameObject {
public:
    void addLicenseText(std::string const& text);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::vector<std::string> m_licenseTexts;
    mutable bool m_showLicenseInfo { false };
};

} // namespace jt
