#ifndef MYAWESOMEGAME_RENDER_WINDOW_TEST_HPP
#define MYAWESOMEGAME_RENDER_WINDOW_TEST_HPP

#include "render_window.hpp"
#include "render_window_interface.hpp"
#include "render_window_null.hpp"
#include <memory>
#include <string>

class RenderWindowFactoryInterface {
public:
    virtual std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title)
        = 0;
};

class RenderWindowFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::RenderWindow>(width, height, title);
    }
};

class RenderWindowNullFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::null_objects::RenderWindowNull>(width, height, title);
    }
};

#endif // MYAWESOMEGAME_RENDER_WINDOW_TEST_HPP
