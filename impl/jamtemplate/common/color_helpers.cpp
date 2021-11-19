#include "color_helpers.hpp"
std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> jt::ColorHelpers::hsv2rgb(
    float h, float s, float v)
{
    s /= 100.0f;
    v /= 100.0f;
    v *= 255.0f;

    float hh, p, q, t, ff;
    long i;
    std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> out;

    if (s <= 0.0f) {
        std::get<0>(out) = static_cast<std::uint8_t>(v);
        std::get<1>(out) = static_cast<std::uint8_t>(v);
        std::get<2>(out) = static_cast<std::uint8_t>(v);
        return out;
    }
    hh = h;
    if (hh >= 360.0f)
        hh = 0.0f;
    hh /= 60.0f;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0f - s);
    q = v * (1.0f - (s * ff));
    t = v * (1.0f - (s * (1.0f - ff)));

    switch (i) {
    case 0: {
        std::get<0>(out) = static_cast<std::uint8_t>(v);
        std::get<1>(out) = static_cast<std::uint8_t>(t);
        std::get<2>(out) = static_cast<std::uint8_t>(p);
        break;
    }
    case 1: {
        std::get<0>(out) = static_cast<std::uint8_t>(q);
        std::get<1>(out) = static_cast<std::uint8_t>(v);
        std::get<2>(out) = static_cast<std::uint8_t>(p);
        break;
    }
    case 2: {
        std::get<0>(out) = static_cast<std::uint8_t>(p);
        std::get<1>(out) = static_cast<std::uint8_t>(v);
        std::get<2>(out) = static_cast<std::uint8_t>(t);
        break;
    }
    case 3: {
        std::get<0>(out) = static_cast<std::uint8_t>(p);
        std::get<1>(out) = static_cast<std::uint8_t>(q);
        std::get<2>(out) = static_cast<std::uint8_t>(v);
        break;
    }
    case 4: {
        std::get<0>(out) = static_cast<std::uint8_t>(t);
        std::get<1>(out) = static_cast<std::uint8_t>(p);
        std::get<2>(out) = static_cast<std::uint8_t>(v);
        break;
    }
    case 5:
    default: {
        std::get<0>(out) = static_cast<std::uint8_t>(v);
        std::get<1>(out) = static_cast<std::uint8_t>(p);
        std::get<2>(out) = static_cast<std::uint8_t>(q);
        break;
    }
    }
    return out;
}
