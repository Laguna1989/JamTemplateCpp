#include "StateMenu.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "InputManager.hpp"
#include "KeyCodes.hpp"
#include "MathHelper.hpp"
#include "SmartDrawableHelpers.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "SmartText.hpp"
#include "StateGame.hpp"
#include "TweenAlpha.hpp"
#include "TweenPosition.hpp"
#include "TweenScale.hpp"

StateMenu::StateMenu() = default;

void StateMenu::doInternalCreate()
{
    float w = static_cast<float>(GP::GetScreenSize().x());
    float h = static_cast<float>(GP::GetScreenSize().y());
    float wC = w / 2;

    m_background = jt::sdh::createRectShape(jt::Vector2 { w, h }, GP::PaletteColor1());
    m_background->update(0.0f);

    m_text_Title = jt::sdh::createText(
        getGame()->getRenderTarget(), GP::GameName(), 32U, GP::PaletteFontFront());
    m_text_Title->setPosition({ wC, 20 });
    m_text_Title->update(0.0f);
    m_text_Title->setShadow(GP::PaletteFontShadow(), jt::Vector2 { 3, 3 });

    m_test_Explanation = jt::sdh::createText(
        getGame()->getRenderTarget(), "Press Space to start the game", 16U, GP::PaletteColor8());
    m_test_Explanation->setPosition({ wC, 150 });
    m_test_Explanation->update(0.0f);
    m_test_Explanation->setShadow(GP::PaletteFontShadow(), jt::Vector2 { 3, 3 });

    m_text_Credits = jt::sdh::createText(getGame()->getRenderTarget(),
        "Created by " + GP::AuthorName() + " for " + GP::JamName() + "\n" + GP::JamDate(), 10U,
        GP::PaletteColor5());
    m_text_Credits->SetTextAlign(jt::SmartText::TextAlign::LEFT);
    m_text_Credits->setPosition({ 10, GP::GetScreenSize().y() - 30 });
    m_text_Credits->update(0.0f);
    m_text_Credits->setShadow(GP::PaletteFontShadow(), jt::Vector2 { 1, 1 });

    m_overlay = jt::sdh::createRectShape(jt::Vector2 { w, h }, jt::colors::Black);
    m_overlay->update(0);

    m_vignette = std::make_shared<jt::SmartSprite>();
    m_vignette->loadSprite("#v#" + std::to_string(static_cast<int>(GP::GetScreenSize().x())) + "#"
        + std::to_string(static_cast<int>(GP::GetScreenSize().y())));
    m_vignette->setIgnoreCamMovement(true);
    m_vignette->setColor({ 255, 255, 255, 100 });

    using tp = jt::TweenPosition<jt::SmartText>;
    using ta = jt::TweenAlpha<jt::SmartText>;
    using ts = jt::TweenScale<jt::SmartText>;
    {
        auto tw = jt::TweenAlpha<jt::SmartShape>::create(
            m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
        tw->setSkipFrames();
        add(tw);
    }

    {
        auto ta1 = ta::create(m_text_Title, 0.55f, 0, 255);
        ta1->setStartDelay(0.2f);
        ta1->setSkipFrames();
        add(ta1);
    }
    {
        auto s2 = m_test_Explanation->getPosition() + jt::Vector2 { -1000, 0 };
        auto e2 = m_test_Explanation->getPosition();

        auto tw2 = tp::create(m_test_Explanation, 0.5f, s2, e2);
        tw2->setStartDelay(0.3f);
        tw2->setSkipFrames();

        tw2->addCompleteCallback([this]() {
            auto ts1 = ts::create(m_test_Explanation, 0.75f, jt::Vector2 { 1.0f, 1.0f },
                jt::Vector2 { 1.05f, 1.05f });
            ts1->setRepeat(true);
            ts1->setAgePercentConversion([](float age) {
                return jt::Lerp::cosine(0.0f, 1.0f, jt::MathHelper::clamp(age, 0.0f, 1.0f));
            });
            add(ts1);
        });
        add(tw2);
    }

    {
        auto s3 = m_text_Credits->getPosition() + jt::Vector2 { 0, 100 };
        auto e3 = m_text_Credits->getPosition();

        auto tw3 = tp::create(m_text_Credits, 0.35f, s3, e3);
        tw3->setStartDelay(0.8f);
        tw3->setSkipFrames();
        add(tw3);
    }
}

void StateMenu::doInternalUpdate(float const elapsed)
{
    m_vignette->update(elapsed);

    checkForTransitionToStateGame();

    m_text_Title->update(elapsed);
    m_test_Explanation->update(elapsed);
    m_text_Credits->update(elapsed);
}

void StateMenu::checkForTransitionToStateGame()
{
    auto const keysToTriggerTransition = { jt::KeyCode::Space, jt::KeyCode::Enter };

    for (auto const k : keysToTriggerTransition) {
        if (jt::InputManager::justPressed(k)) {
            startTransitionToStateGame();
        }
    }
}

void StateMenu::startTransitionToStateGame()
{
    if (!m_started) {
        m_started = true;

        auto tw = jt::TweenAlpha<jt::SmartShape>::create(
            m_overlay, 0.5f, std::uint8_t { 0 }, std::uint8_t { 255 });
        tw->setSkipFrames();
        tw->addCompleteCallback(
            [this]() { getGame()->switchState(std::make_shared<StateGame>()); });
        add(tw);
    }
}

void StateMenu::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());

    m_text_Title->draw(getGame()->getRenderTarget());
    m_test_Explanation->draw(getGame()->getRenderTarget());
    m_text_Credits->draw(getGame()->getRenderTarget());

    m_overlay->draw(getGame()->getRenderTarget());
    m_vignette->draw(getGame()->getRenderTarget());
}
