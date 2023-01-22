#include "group_volume_manager.hpp"
#include <algorithm>

float jt::GroupVolumeManager::getVolume(std::string const& groupName) const
{
    if (groupName == "") {
        return 1.0f;
    }
    if (m_volumeGroups.count(groupName) == 0) {
        m_volumeGroups[groupName] = 1.0f;
    }

    return m_volumeGroups[groupName];
}

void jt::GroupVolumeManager::setGroupVolume(std::string const& groupName, float volume)
{
    m_volumeGroups[groupName] = volume;
}
std::vector<std::string> jt::GroupVolumeManager::getAllGroupNames() const
{
    std::vector<std::string> groupNames;
    groupNames.resize(m_volumeGroups.size());
    std::transform(m_volumeGroups.cbegin(), m_volumeGroups.cend(), groupNames.begin(),
        [](auto const& kvp) { return kvp.first; });
    return groupNames;
}
