#ifndef STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD

#include "button.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_state.hpp"
#include "text.hpp"
#include <memory>

namespace detail {
constexpr float buttonOffsetX = 64;
constexpr float buttonOffsetY = 16;
constexpr float buttonMarginY = 8;
constexpr unsigned int buttonSizeX = 100;
constexpr unsigned int buttonSizeY = 16;
} // namespace detail

class StateSelect : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::size_t m_buttonCount { 0U };

    template <class State>
    void AddButton(std::string const& textString)
    {
        float posY
            = detail::buttonOffsetY + m_buttonCount * (detail::buttonMarginY + detail::buttonSizeY);
        auto const button = std::make_shared<jt::Button>(
            jt::Vector2u { detail::buttonSizeX, detail::buttonSizeY });
        button->addCallback([this]() { getGame()->switchState(std::make_shared<State>()); });
        auto const text = jt::dh::createText(getGame()->getRenderTarget(), textString, 12);
        text->setTextAlign(jt::Text::TextAlign::LEFT);
        text->setOrigin(jt::Vector2 { -8, 0 });
        button->setDrawable(text);
        button->setPosition(jt::Vector2 { detail::buttonOffsetX, posY });
        add(std::move(button));

        m_buttonCount++;
    }
};

#endif
