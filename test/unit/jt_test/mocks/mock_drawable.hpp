#ifndef JAMTEMPLATE_UNITTEST_MOCKDRAWABLE_HPP
#define JAMTEMPLATE_UNITTEST_MOCKDRAWABLE_HPP

#include <graphics/drawable_interface.hpp>
#include <render_target_layer.hpp>
#include <gmock/gmock.h>
#include <memory>

class MockDrawable : public jt::DrawableInterface {
public:
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::RenderTargetInterface>), (const, override));

    MOCK_METHOD(void, update, (float), (override));

    MOCK_METHOD(void, flash, (float, jt::Color), (override));
    MOCK_METHOD(void, shake, (float, float, float), (override));

    MOCK_METHOD(void, flicker, (float, float), (override));

    MOCK_METHOD(void, setColor, (jt::Color const&), (override));
    MOCK_METHOD(jt::Color, getColor, (), (const, override));

    MOCK_METHOD(void, setPosition, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getPosition, (), (const, override));

    MOCK_METHOD(jt::Vector2f, getScreenPosition, (), (const, override));

    MOCK_METHOD(jt::Rectf, getGlobalBounds, (), (const, override));
    MOCK_METHOD(jt::Rectf, getLocalBounds, (), (const, override));

    MOCK_METHOD(void, setFlashColor, (jt::Color const&), (override));
    MOCK_METHOD(jt::Color, getFlashColor, (), (const, override));

    MOCK_METHOD(void, setScale, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getScale, (), (const, override));

    MOCK_METHOD(void, setOrigin, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getOrigin, (), (const, override));
    MOCK_METHOD(void, setOrigin, (jt::OriginMode), (override));
    MOCK_METHOD(jt::OriginMode, getOriginMode, (), (const, override));

    MOCK_METHOD(jt::Vector2f, getOffset, (), (const, override));
    MOCK_METHOD(void, setOffset, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::OffsetMode, getOffsetMode, (), (const, override));
    MOCK_METHOD(void, setOffset, (jt::OffsetMode), (override));

    MOCK_METHOD(void, setRotation, (float), (override));
    MOCK_METHOD(float, getRotation, (), (const, override));

    MOCK_METHOD(void, setShadowActive, (bool), (override));
    MOCK_METHOD(bool, getShadowActive, (), (const, override));
    MOCK_METHOD(jt::Color, getShadowColor, (), (const, override));
    MOCK_METHOD(jt::Vector2f, getShadowOffset, (), (const, override));
    MOCK_METHOD(void, setShadow, (jt::Color const&, jt::Vector2f const&), (override));

    MOCK_METHOD(bool, getOutlineActive, (), (const, override));
    MOCK_METHOD(void, setOutline, (jt::Color const&, int), (override));
    MOCK_METHOD(jt::Color, getOutlineColor, (), (const, override));
    MOCK_METHOD(int, getOutlineWidth, (), (const, override));

    MOCK_METHOD(void, setIgnoreCamMovement, (bool), (override));
    MOCK_METHOD(bool, getIgnoreCamMovement, (), (const, override));

    MOCK_METHOD(void, setScreenSizeHint, (jt::Vector2f const& hint), (override));
    MOCK_METHOD(jt::Vector2f, getScreenSizeHint, (), (const, override));

    MOCK_METHOD(void, setBlendMode, (jt::BlendMode), (override));
    MOCK_METHOD(jt::BlendMode, getBlendMode, (), (const, override));

    MOCK_METHOD(bool, isVisible, (), (const, override));

    MOCK_METHOD(void, setCamMovementFactor, (float), (override));
    MOCK_METHOD(float, getCamMovementFactor, (), (const, override));

    MOCK_METHOD(void, setZ, (int), (override));
    MOCK_METHOD(int, getZ, (), (const, override));
};

#endif
