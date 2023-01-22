#include <audio/group_volume_manager.hpp>
#include <gtest/gtest.h>

TEST(GroupVolumeManagerTest, InitialVolumeIsOne)
{
    jt::GroupVolumeManager manager;
    ASSERT_EQ(manager.getVolume(""), 1.0f);
    ASSERT_EQ(manager.getVolume("master"), 1.0f);
    ASSERT_EQ(manager.getVolume("blarzblurz"), 1.0f);
}

TEST(GroupVolumeManagerTest, VolumeAfterSet)
{
    jt::GroupVolumeManager manager;
    manager.setGroupVolume("master", 0.5f);
    ASSERT_EQ(manager.getVolume("master"), 0.5f);
}

TEST(GroupVolumeManagerTest, InitialListOfGroupsIsEmpty)
{
    jt::GroupVolumeManager manager;
    ASSERT_EQ(manager.getAllGroupNames().size(), 0U);
}

TEST(GroupVolumeManagerTest, ListOfGroupsIsExtendedBySetVolume)
{
    jt::GroupVolumeManager manager;
    manager.setGroupVolume("bla", 1.0f);
    manager.setGroupVolume("blubb", 1.0f);
    auto const allGroups = manager.getAllGroupNames();
    ASSERT_EQ(allGroups.size(), 2u);
    ASSERT_EQ(allGroups.at(0), "bla");
    ASSERT_EQ(allGroups.at(1), "blubb");
}

TEST(GroupVolumeManagerTest, ListOfGroupsIsExtendedByGetVolume)
{
    jt::GroupVolumeManager manager;
    (void)manager.getVolume("bla");
    (void)manager.getVolume("blubb");
    auto const allGroups = manager.getAllGroupNames();
    ASSERT_EQ(allGroups.size(), 2u);
    ASSERT_EQ(allGroups.at(0), "bla");
    ASSERT_EQ(allGroups.at(1), "blubb");
}
