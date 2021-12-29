#ifndef GUARD_JAMTEMAPLTE_RENDER_WINDOW_TEST_HPP
#define GUARD_JAMTEMAPLTE_RENDER_WINDOW_TEST_HPP

#include "render_window.hpp"
#include "render_window_interface.hpp"
#include "render_window_null.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

class RenderWindowFactoryInterface {
public:
    virtual ~RenderWindowFactoryInterface() = default;
    virtual std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title)
        = 0;
    virtual void checkRenderTarget(std::shared_ptr<jt::RenderTarget> target) = 0;
};

class RenderWindowFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::RenderWindow>(width, height, title);
    }
    void checkRenderTarget(std::shared_ptr<jt::RenderTarget> target) override
    {
        ASSERT_NE(target, nullptr);
    }
};

class RenderWindowNullFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::null_objects::RenderWindowNull>(width, height, title);
    }
    void checkRenderTarget(std::shared_ptr<jt::RenderTarget> target) override
    {
        ASSERT_EQ(target, nullptr);
    }
};

#endif // GUARD_JAMTEMAPLTE_RENDER_WINDOW_TEST_HPP
