#include <tilemap/tilemap_cache_null.hpp>
#include <gtest/gtest.h>

TEST(TilemapCacheNullTest, GetMapReturnsNoNullptr)
{
    jt::TilemapCacheNull cache;
    ASSERT_NE(cache.get("abcd"), nullptr);
}

TEST(TilemapCacheNullTest, GetMapReturnsAlwaysTheSamePointer)
{
    jt::TilemapCacheNull cache;

    auto const p1 = cache.get("abcd");
    auto const p2 = cache.get("xyz1");

    ASSERT_EQ(p1, p2);
}
