#ifndef JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SPRITEFUNCTIONS_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <vector>

namespace JamTemplate {

class SpriteFunctions {
public:
    SpriteFunctions() = delete;

    static void makeButtonImage(sf::Image& img, unsigned int w, unsigned int h, sf::Color midColor = sf::Color { 200, 200, 200 }, sf::Color darkColor = sf::Color { 100, 100, 100 }, sf::Color brightColor = sf::Color { 255, 255, 255 })
    {
        img.create(3 * w, h, midColor);

        for (unsigned int i = 0; i != w; ++i) {
            img.setPixel(i, 0, brightColor);
            img.setPixel(i, h - 1, darkColor);

            img.setPixel(2 * w + i, 0, darkColor);
            img.setPixel(2 * w + i, h - 1, brightColor);
        }

        for (unsigned int j = 0; j != h; ++j) {
            img.setPixel(0, j, brightColor);
            img.setPixel(w - 1, j, darkColor);

            img.setPixel(2 * w, j, darkColor);
            img.setPixel(3 * w - 1, j, brightColor);
        }
    }
};

} // namespace JamTemplate

#endif
