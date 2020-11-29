#ifndef STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "SmartShape.hpp"
#include "TweenAlpha.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class StateTween : public jt::GameState {
public:
    StateTween() = default;

private:
    jt::SmartShape::Sptr m_overlayR;
    jt::SmartShape::Sptr m_overlayG;
    jt::SmartShape::Sptr m_overlayB;
    jt::SmartShape::Sptr m_background;

    void doInternalUpdate(float const /*elapsed*/) override;

    void doCreate() override
    {

        m_background = std::make_shared<jt::SmartShape>();
        m_background->makeRect(jt::vector2(200, 150));
        m_background->setColor(jt::color { 255, 255, 255 });

        using jt::SmartShape;
        using jt::TweenAlpha;

        m_overlayR = std::make_shared<SmartShape>();
        m_overlayR->makeRect(jt::vector2 { 200, 200 });
        m_overlayR->setColor(jt::color { 255, 0, 0, 0 });

        m_overlayG = std::make_shared<SmartShape>();
        m_overlayG->makeRect(jt::vector2 { 200, 200 });
        m_overlayG->setColor(jt::color { 0, 255, 0, 0 });

        m_overlayB = std::make_shared<SmartShape>();
        m_overlayB->makeRect(jt::vector2 { 200, 200 });
        m_overlayB->setColor(jt::color { 0, 0, 255, 0 });

        auto twRIn = TweenAlpha<SmartShape>::create(
            m_overlayR, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
        twRIn->addCompleteCallback([this]() {
            auto twROut = TweenAlpha<SmartShape>::create(
                m_overlayR, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
            twROut->setStartDelay(1.5f);
            add(twROut);
        });
        add(twRIn);

        auto twGIn = TweenAlpha<SmartShape>::create(
            m_overlayG, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
        twGIn->setStartDelay(2.0f);
        twGIn->addCompleteCallback([this]() {
            auto twGOut = TweenAlpha<SmartShape>::create(
                m_overlayG, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
            twGOut->setStartDelay(1.5f);
            add(twGOut);
        });
        add(twGIn);

        auto twBIn = TweenAlpha<SmartShape>::create(
            m_overlayB, 1.0f, std::uint8_t { 0 }, std::uint8_t { 125 });
        twBIn->setStartDelay(4.0f);
        twBIn->addCompleteCallback([this]() {
            auto twBOut = TweenAlpha<SmartShape>::create(
                m_overlayB, 1.0, std::uint8_t { 125 }, std::uint8_t { 0 });
            twBOut->setStartDelay(1.5f);
            add(twBOut);
        });
        add(twBIn);

        m_background->update(0);
        m_overlayR->update(0);
        m_overlayG->update(0);
        m_overlayB->update(0);
    }

    void doInternalDraw() const override
    {
        m_background->draw(getGame()->getRenderTarget());

        drawObjects();

        m_overlayR->draw(getGame()->getRenderTarget());
        m_overlayG->draw(getGame()->getRenderTarget());
        m_overlayB->draw(getGame()->getRenderTarget());
    }
};

#endif
