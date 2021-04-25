﻿#include "StateTween.hpp"
#include "DrawableHelpers.hpp"
#include "GameInterface.hpp"
#include "InputManager.hpp"
#include "StateSelect.hpp"

void StateTween::doInternalCreate()
{
    createRects();
    createTweens();
}

void StateTween::createRects()
{
    m_background = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::colors::White);

    m_overlayR = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::colors::Red);
    m_overlayG = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::colors::Green);
    m_overlayB = jt::dh::createRectShape(jt::Vector2 { 400, 300 }, jt::colors::Blue);
}

void StateTween::createTweens()
{
    using ta = jt::TweenAlpha<jt::Shape>;

    auto twRIn = ta::create(m_overlayR, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
    twRIn->addCompleteCallback([this]() {
        auto twROut = ta::create(m_overlayR, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
        twROut->setStartDelay(1.5f);
        add(twROut);
    });
    add(twRIn);

    auto twGIn = ta::create(m_overlayG, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
    twGIn->setStartDelay(2.0f);
    twGIn->addCompleteCallback([this]() {
        auto twGOut = ta::create(m_overlayG, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
        twGOut->setStartDelay(1.5f);
        add(twGOut);
    });
    add(twGIn);

    auto twBIn = ta::create(m_overlayB, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
    twBIn->setStartDelay(4.0f);
    twBIn->addCompleteCallback([this]() {
        auto twBOut = ta::create(m_overlayB, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
        twBOut->setStartDelay(1.5f);
        add(twBOut);
    });
    add(twBIn);
}

void StateTween::doInternalUpdate(float const elapsed)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }

    m_background->update(elapsed);
    m_overlayR->update(elapsed);
    m_overlayG->update(elapsed);
    m_overlayB->update(elapsed);
}

void StateTween::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());

    m_overlayR->draw(getGame()->getRenderTarget());
    m_overlayG->draw(getGame()->getRenderTarget());
    m_overlayB->draw(getGame()->getRenderTarget());
}
