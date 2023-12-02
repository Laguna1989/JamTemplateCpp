#include <cache/cache_null.hpp>
#include <gtest/gtest.h>

TEST(CacheNullTest, ReturnsSameInstance)
{
    jt::CacheNull cache;
    auto& t1 = cache.getTilemapCache();
    auto& t2 = cache.getTilemapCache();

    ASSERT_EQ(&t1, &t2);
}
