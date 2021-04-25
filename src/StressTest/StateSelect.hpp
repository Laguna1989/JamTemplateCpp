#ifndef STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD

#include "Button.hpp"
#include "DrawableHelpers.hpp"
#include "GameInterface.hpp"
#include "GameState.hpp"
#include "Text.hpp"
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
    void AddButton(std::string const& textString)
    {
        float posY
            = detail::buttonOffsetY + m_buttonCount * (detail::buttonMarginY + detail::buttonSizeY);
        auto const button = std::make_shared<jt::Button>(
            jt::Vector2u { detail::buttonSizeX, detail::buttonSizeY });
        button->addCallback([this]() { getGame()->switchState(std::make_shared<State>()); });
        auto const text = jt::dh::createText(getGame()->getRenderTarget(), textString, 28);
        text->SetTextAlign(jt::Text::TextAlign::LEFT);
        button->setDrawable(text);
        button->setPosition(jt::Vector2 { detail::buttonOffsetX, posY });
        add(std::move(button));

        m_buttonCount++;
    }
};

#endif
