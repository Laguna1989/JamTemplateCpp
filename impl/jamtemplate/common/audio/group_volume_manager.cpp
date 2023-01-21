#include "group_volume_manager.hpp"

float jt::GroupVolumeManager::getVolume(std::string const& groupName) const
{
    return getVolumeFromGroup("master") * getVolumeFromGroup(groupName);
}

float jt::GroupVolumeManager::getVolumeFromGroup(std::string const& groupName) const
{
    if (m_volumeGroups.count(groupName) == 0) {
        m_volumeGroups[groupName] = 1.0f;
    }

    return m_volumeGroups[groupName];
}

void jt::GroupVolumeManager::setGroupVolume(std::string const& groupName, float volume)
{
    m_volumeGroups[groupName] = volume;
}
