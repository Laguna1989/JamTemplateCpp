#include "color_helpers.hpp"
#include <sstream>
#include <stdexcept>

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

namespace {
std::uint8_t hexStringToUint8(std::string const& input)
{
    std::stringstream ss;
    ss << std::hex << input;
    int value;
    ss >> value;
    return static_cast<std::uint8_t>(value);
}

} // namespace

std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> jt::ColorHelpers::hex2rgb(
    std::string const& hexString)
{
    auto tempString = hexString;
    if (hexString.front() == '#') {
        tempString = hexString.substr(1);
    }
    if (tempString.size() != 6) {
        throw std::invalid_argument { "invalid color hex string '" + tempString + "'" };
    }
    auto const rString = tempString.substr(0, 2);
    auto const gString = tempString.substr(2, 2);
    auto const bString = tempString.substr(4, 2);

    return std::make_tuple(
        hexStringToUint8(rString), hexStringToUint8(gString), hexStringToUint8(bString));
}
std::tuple<float, float, float> jt::ColorHelpers::rgb2hsv(
    std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    std::tuple<float, float, float> out;
    float min, max, delta;

    min = r < g ? r : g;
    min = min < b ? min : b;

    max = r > g ? r : g;
    max = max > b ? max : b;

    std::get<2>(out) = max * 100.0f / 255.0f; // v
    delta = max - min;
    if (delta < 0.00001f) {
        std::get<1>(out) = 0.0f;
        std::get<0>(out) = 0.0f; // undefined, maybe nan?
        return out;
    }
    if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
        std::get<1>(out) = (delta / max) * 100.0f; // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        std::get<1>(out) = 0.0;
        std::get<0>(out) = 0.0f; // its now undefined
        return out;
    }
    if (r >= max) // > is bogus, just keeps compilor happy
        std::get<0>(out) = (g - b) / delta; // between yellow & magenta
    else if (g >= max)
        std::get<0>(out) = 2.0f + (b - r) / delta; // between cyan & yellow
    else
        std::get<0>(out) = 4.0f + (r - g) / delta; // between magenta & cyan

    std::get<0>(out) *= 60.0f; // degrees

    if (std::get<0>(out) < 0.0f)
        std::get<0>(out) += 360.0f;

    return out;
}
