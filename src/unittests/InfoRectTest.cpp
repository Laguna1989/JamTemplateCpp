#include "info_rect.hpp"
#include <gtest/gtest.h>

TEST(InfoRectTest, ContainsStoredValues)
{
    jt::Vector2 const pos { 100.0f, 40.5f };
    jt::Vector2 const size { 20.0f, 30.f };
    float const angle { 45.0f };
    std::string const type { "type" };
    jt::InfoRect r { pos, size, angle, type };

    EXPECT_EQ(r.type, type);
    EXPECT_EQ(r.position, pos);
    EXPECT_EQ(r.rotation, angle);
    EXPECT_EQ(r.sizeDiagonal, size);
}
