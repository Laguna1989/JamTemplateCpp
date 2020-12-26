#ifndef STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD

#include "Button.hpp"
#include "GameState.hpp"
#include "SmartText.hpp"
#include <memory>

namespace detail {
constexpr float buttonOffsetX = 64;
constexpr float buttonOffsetY = 16;
constexpr float buttonMarginY = 8;
constexpr unsigned int buttonSizeX = 184;
constexpr unsigned int buttonSizeY = 32;
} // namespace detail

class StateSelect : public jt::GameState {

private:
    virtual void doInternalCreate() override;
    virtual void doInternalUpdate(float elapsed) override;
    virtual void doInternalDraw() const override;

    std::size_t m_buttonCount { 0U };

    template <class State>
    void AddButton(std::string const& text)
    {
        float posY
            = detail::buttonOffsetY + m_buttonCount * (detail::buttonMarginY + detail::buttonSizeY);
        auto const b = std::make_shared<jt::Button>(
            jt::Vector2u { detail::buttonSizeX, detail::buttonSizeY });
        b->addCallback([this]() { getGame()->switchState(std::make_shared<State>()); });
        auto const t = std::make_shared<jt::SmartText>();
        t->loadFont("assets/font.ttf", 28, getGame()->getRenderTarget());
        t->setText(text);
        // t->setOffset(jt::Vector2 { 32.0f, 6.0f });
        t->SetTextAlign(jt::SmartText::TextAlign::LEFT);
        b->setDrawable(t);
        b->setPosition(jt::Vector2 { detail::buttonOffsetX, posY });
        add(std::move(b));

        m_buttonCount++;
    }
};

#endif
