#include "state_tween.hpp"
#include "../state_select.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "tweens/tween_alpha.hpp"
#include <cstdint>

void StateTween::doInternalCreate()
{
    createRects();
    createTweens();
    storeActionCommand(getGame()->getActionCommandManager().registerTemporaryCommand(
        "start_tweens", [this](auto /*str*/) { createTweens(); }));
}

void StateTween::createRects()
{
    m_background = jt::dh::createShapeRect(
        jt::Vector2f { 400, 300 }, jt::colors::White, getGame()->gfx().textureManager());

    m_overlayR = jt::dh::createShapeRect(
        jt::Vector2f { 400, 300 }, jt::colors::Red, getGame()->gfx().textureManager());
    m_overlayG = jt::dh::createShapeRect(
        jt::Vector2f { 400, 300 }, jt::colors::Green, getGame()->gfx().textureManager());
    m_overlayB = jt::dh::createShapeRect(
        jt::Vector2f { 400, 300 }, jt::colors::Blue, getGame()->gfx().textureManager());
}

void StateTween::createTweens()
{
    using ta = jt::TweenAlpha;

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
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }

    m_background->update(elapsed);
    m_overlayR->update(elapsed);
    m_overlayG->update(elapsed);
    m_overlayB->update(elapsed);
}

void StateTween::doInternalDraw() const
{
    m_background->draw(getGame()->gfx().target());

    m_overlayR->draw(getGame()->gfx().target());
    m_overlayG->draw(getGame()->gfx().target());
    m_overlayB->draw(getGame()->gfx().target());
}
std::string StateTween::getName() const { return "Tweens"; }
