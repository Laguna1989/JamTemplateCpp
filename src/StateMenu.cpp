#include "StateMenu.hpp"
#include "GameProperties.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/InputManager.hpp"
#include "JamTemplate/MathHelper.hpp"
#include "JamTemplate/SmartShape.hpp"
#include "JamTemplate/SmartText.hpp"
#include "JamTemplate/TextureManager.hpp"
#include "JamTemplate/TweenAlpha.hpp"
#include "JamTemplate/TweenPosition.hpp"
#include "JamTemplate/TweenScale.hpp"
#include "StateGame.hpp"

StateMenu::StateMenu() = default;
void StateMenu::doInternalUpdate(float const elapsed)
{
    if (!m_starting) {
        using ip = JamTemplate::InputManager;
        if (ip::justPressed(sf::Keyboard::Key::Space)
            || ip::justPressed(sf::Keyboard::Key::Return)) {

            m_starting = true;
            auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(
                m_overlay, 0.5f, sf::Uint8 { 0 }, sf::Uint8 { 255 });
            tw->setSkipFrames();
            tw->addCompleteCallback(
                [this]() { getGame()->switchState(std::make_shared<StateGame>()); });
            add(tw);
        }

        m_text_Title->update(elapsed);
        m_test_Explanation->update(elapsed);
    }
}

void StateMenu::doCreate()
{
    float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
    float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
    float wC = w / 2;

    m_background = std::make_shared<JamTemplate::SmartShape>();
    m_background->makeRect({ w, h });
    m_background->setColor(GP::PaletteColor1());
    m_background->update(0.0f);

    m_text_Title = std::make_shared<JamTemplate::SmartText>();
    m_text_Title->loadFont("assets/font.ttf");
    m_text_Title->setCharacterSize(32U);
    m_text_Title->setText(GP::GameName());
    m_text_Title->setPosition({ wC, 20 });
    m_text_Title->setColor(GP::PaletteColor3());
    m_text_Title->update(0.0f);
    m_text_Title->SetTextAlign(JamTemplate::SmartText::TextAlign::CENTER);
    m_text_Title->setShadow(GP::PaletteFontShadow(), sf::Vector2f { 3, 3 });

    m_test_Explanation = std::make_shared<JamTemplate::SmartText>();
    m_test_Explanation->loadFont("assets/font.ttf");
    m_test_Explanation->setCharacterSize(16U);
    m_test_Explanation->setText("Press Space to start the game");
    m_test_Explanation->setPosition({ wC, 150 });
    m_test_Explanation->setColor(GP::PaletteColor4());
    m_test_Explanation->update(0.0f);
    auto const textWidth = m_test_Explanation->getLocalBounds().width;
    auto const textHeight = m_test_Explanation->getLocalBounds().height;
    m_test_Explanation->setOrigin(sf::Vector2f { textWidth / 2, textHeight / 2 });
    m_test_Explanation->SetTextAlign(JamTemplate::SmartText::TextAlign::LEFT);
    m_test_Explanation->setShadow(GP::PaletteFontShadow(), sf::Vector2f { 3, 3 });

    m_text_Credits = std::make_shared<JamTemplate::SmartText>();
    m_text_Credits->loadFont("assets/font.ttf");
    m_text_Credits->setCharacterSize(10U);
    m_text_Credits->setText("Created by @Laguna_999 for #1hgj288\nHalloween2020");
    m_text_Credits->setPosition({ 10, 265 });
    m_text_Credits->setColor(GP::PaletteColor5());
    m_text_Credits->SetTextAlign(JamTemplate::SmartText::TextAlign::LEFT);
    m_text_Credits->update(0.0f);
    m_text_Credits->setShadow(GP::PaletteFontShadow(), sf::Vector2f { 1, 1 });

    m_overlay = std::make_shared<JamTemplate::SmartShape>();
    m_overlay->makeRect(sf::Vector2f { w, h });
    m_overlay->setColor(sf::Color { 0, 0, 0 });
    m_overlay->update(0);

    using tp = JamTemplate::TweenPosition<JamTemplate::SmartText>;
    using ta = JamTemplate::TweenAlpha<JamTemplate::SmartText>;
    using ts = JamTemplate::TweenScale<JamTemplate::SmartText>;
    {
        auto tw = JamTemplate::TweenAlpha<JamTemplate::SmartShape>::create(
            m_overlay, 0.5f, sf::Uint8 { 255 }, sf::Uint8 { 0 });
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
        auto s2 = m_test_Explanation->getPosition() + sf::Vector2f { -500, 0 };
        auto e2 = m_test_Explanation->getPosition();

        auto tw2 = tp::create(m_test_Explanation, 0.5f, s2, e2);
        tw2->setStartDelay(0.3f);
        tw2->setSkipFrames();

        tw2->addCompleteCallback([this]() {
            auto ts1 = ts::create(m_test_Explanation, 0.75f, sf::Vector2f { 1.0f, 1.0f },
                sf::Vector2f { 1.05f, 1.05f });
            ts1->setRepeat(true);
            ts1->setAgePercentConversion([](float age) {
                return JamTemplate::Lerp::cosine(
                    0.0f, 1.0f, JamTemplate::MathHelper::clamp(age, 0.0f, 1.0f));
            });
            add(ts1);
        });
        add(tw2);
    }

    {
        auto s3 = m_text_Credits->getPosition() + sf::Vector2f { 0, 100 };
        auto e3 = m_text_Credits->getPosition();

        auto tw3 = tp::create(m_text_Credits, 0.35f, s3, e3);
        tw3->setStartDelay(0.8f);
        tw3->setSkipFrames();
        add(tw3);
    }
}
void StateMenu::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());

    m_text_Title->draw(getGame()->getRenderTarget());
    m_test_Explanation->draw(getGame()->getRenderTarget());
    m_text_Credits->draw(getGame()->getRenderTarget());

    m_overlay->draw(getGame()->getRenderTarget());
}
