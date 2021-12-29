#ifndef JAMTEMPLATE_UNITTEST_MOCKDRAWABLE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKDRAWABLE_HPP_INCLUDEGUARD

#include "drawable_interface.hpp"
#include "render_target.hpp"
#include <gmock/gmock.h>
#include <memory>

class MockDrawable : public jt::DrawableInterface {
public:
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::RenderTarget>), (const, override));
    MOCK_METHOD(void, flash, (float, jt::Color), (override));
    MOCK_METHOD(void, shake, (float, float, float), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(void, setColor, (jt::Color const&), (override));
    MOCK_METHOD(jt::Color, getColor, (), (const, override));
    MOCK_METHOD(void, setPosition, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getPosition, (), (const, override));
    MOCK_METHOD(jt::Rectf, getGlobalBounds, (), (const, override));
    MOCK_METHOD(jt::Rectf, getLocalBounds, (), (const, override));
    MOCK_METHOD(void, setFlashColor, (jt::Color const&), (override));
    MOCK_METHOD(jt::Color, getFlashColor, (), (const, override));
    MOCK_METHOD(void, setScale, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getScale, (), (const, override));
    MOCK_METHOD(void, setOrigin, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getOrigin, (), (const, override));
    MOCK_METHOD(jt::Vector2f, getOffset, (), (const, override));
    MOCK_METHOD(void, setOffset, (jt::Vector2f const), (override));
    MOCK_METHOD(void, setRotation, (float), (override));
    MOCK_METHOD(float, getRotation, (), (const, override));
    MOCK_METHOD(void, setShadowActive, (bool), (override));
    MOCK_METHOD(bool, getShadowActive, (), (const, override));
    MOCK_METHOD(void, setShadowColor, (jt::Color const&), (override));
    MOCK_METHOD(jt::Color, getShadowColor, (), (const, override));
    MOCK_METHOD(void, setShadowOffset, (jt::Vector2f const&), (override));
    MOCK_METHOD(jt::Vector2f, getShadowOffset, (), (const, override));
    MOCK_METHOD(void, setShadow, (jt::Color const&, jt::Vector2f const&), (override));
    MOCK_METHOD(void, setIgnoreCamMovement, (bool), (override));
    MOCK_METHOD(bool, getIgnoreCamMovement, (), (const, override));
};

#endif
