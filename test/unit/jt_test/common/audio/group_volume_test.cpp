#include <audio/group_volume_manager.hpp>
#include <gtest/gtest.h>

TEST(SoundGroupManagerTest, InitialVolumeIsOne)
{
    jt::GroupVolumeManager manager;
    ASSERT_EQ(manager.getVolume(""), 1.0f);
    ASSERT_EQ(manager.getVolume("master"), 1.0f);
    ASSERT_EQ(manager.getVolume("blarzblurz"), 1.0f);
}

TEST(SoundGroupManagerTest, VolumeAfterSet)
{
    jt::GroupVolumeManager manager;
    manager.setGroupVolume("master", 0.5f);
    ASSERT_EQ(manager.getVolume(""), 0.5f);
}
