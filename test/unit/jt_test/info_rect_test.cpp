#include "info_rect.hpp"
#include <gtest/gtest.h>
#include <type_traits>

TEST(InfoRectTest, CanBeDefaultConstructed)
{
    ASSERT_TRUE(std::is_default_constructible<jt::InfoRect>::value);
}

TEST(InfoRectTest, ContainsStoredValues)
{
    jt::Vector2 const pos { 100.0f, 40.5f };
    jt::Vector2 const size { 20.0f, 30.f };
    float const angle { 45.0f };
    std::string const type { "type" };
    jt::InfoRect r { pos, size, angle, type };

    ASSERT_EQ(r.type, type);
    ASSERT_EQ(r.position, pos);
    ASSERT_EQ(r.rotation, angle);
    ASSERT_EQ(r.size, size);
}
