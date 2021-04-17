#ifndef GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP
#define GUARD_JAMTEMPLATE_RENDERWINDOW_LIB_GUARD_HPP

#include "RenderWindowInterface.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>

namespace sf {
class RenderWindow;
} // namespace sf

namespace jt {
class RenderWindow : public RenderWindowInterface {
public:
    RenderWindow(unsigned int width, unsigned int height, std::string const& title);

    virtual bool isOpen() const override;
    virtual void checkForClose() override;

    virtual jt::Vector2 getSize() const override;

    virtual void draw(std::shared_ptr<jt::Sprite>) override;

    virtual void display() override;

private:
    std::shared_ptr<sf::RenderWindow> m_window;
};
} // namespace jt

#endif
