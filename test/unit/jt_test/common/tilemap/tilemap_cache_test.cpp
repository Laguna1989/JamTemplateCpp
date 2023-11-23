#include <preload_helper.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <gtest/gtest.h>

TEST(TilemapCachePreload, ReturnsNonZeroEntries)
{
    jt::TilemapCache cache;
    jt::PreloadHelper::preloadAllFrom(
        cache, "assets/test/unit/jt_test/tileson_test_maps_for_preload", "json", false);
    ASSERT_EQ(cache.getNumberOfMaps(), 2);
}
