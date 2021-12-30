#ifndef MYAWESOMEGAME_MOCK_GFX_HPP
#define MYAWESOMEGAME_MOCK_GFX_HPP

#include "gfx_interface.hpp"
#include "mock_camera.hpp"
#include "mock_window.hpp"
#include "texture_manager_impl.hpp"
#include <gmock/gmock.h>

class MockGfx : public jt::GfxInterface {
public:
    MOCK_METHOD(jt::RenderWindowInterface&, window, (), (override));
    MOCK_METHOD(jt::CamInterface&, camera, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::RenderTarget>, target, (), (override));
    MOCK_METHOD(jt::TextureManagerInterface&, textureManager, (), (override));

    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(void, clear,(), (override));
    MOCK_METHOD(void, display, (), (override));

};

#endif // MYAWESOMEGAME_MOCK_GFX_HPP
