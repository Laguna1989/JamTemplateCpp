#ifndef JAMTEMPLATE_LICENSE_INFO_HPP
#define JAMTEMPLATE_LICENSE_INFO_HPP

#include <game_object.hpp>
#include <string>

namespace jt {

class LicenseInfo : public GameObject {
public:
    void addLicenseText(std::string const& text);

private:
    virtual void doCreate();
    virtual void doUpdate(float const /*elapsed*/);
    virtual void doDraw() const;

    std::vector<std::string> m_licenseTexts;
    mutable bool m_showLicenseInfo { false };
};

} // namespace jt

#endif // JAMTEMPLATE_LICENSE_INFO_HPP
