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

    /*jt::RenderWindowInterface& m_window;
    ::testing::NiceMock<MockCamera> m_camera;
    jt::TextureManagerImpl m_textureManager;*/
};

#endif // MYAWESOMEGAME_MOCK_GFX_HPP
