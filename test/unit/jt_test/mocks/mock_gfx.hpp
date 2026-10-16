#ifndef JAMTEMPLATE_MOCK_GFX_HPP
#define JAMTEMPLATE_MOCK_GFX_HPP

#include <graphics/gfx_interface.hpp>
#include <mocks/mock_camera.hpp>
#include <mocks/mock_window.hpp>
#include <mocks/render_target_stub.hpp>
#include <texture_manager_impl.hpp>
#include <gmock/gmock.h>

class MockGfx : public jt::GfxInterface {
public:
    MockGfx()
    {
        ON_CALL(*this, target()).WillByDefault(::testing::ReturnRef(m_renderTargetStub));
    }

    MOCK_METHOD(jt::RenderWindowInterface&, window, (), (override));
    MOCK_METHOD(jt::CamInterface&, camera, (), (override));
    MOCK_METHOD(jt::RenderTargetInterface&, target, (), (override));
    MOCK_METHOD(jt::TextureManagerInterface&, textureManager, (), (override));

    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, display, (), (override));

    MOCK_METHOD(void, createZLayer, (int), (override));

    RenderTargetStub m_renderTargetStub;
};

#endif // JAMTEMPLATE_MOCK_GFX_HPP
