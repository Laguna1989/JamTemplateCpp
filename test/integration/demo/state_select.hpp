#ifndef STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SELECT_HPP_INCLUDEGUARD

#include "button.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_state.hpp"
#include "text.hpp"
#include <memory>

namespace detail {
constexpr float buttonOffsetX = 16;
constexpr float buttonOffsetY = 16;
constexpr float buttonMarginY = 8;
constexpr float buttonMarginX = 8;
constexpr unsigned int buttonSizeX = 100;
constexpr unsigned int buttonSizeY = 16;

} // namespace detail

class StateSelect : public jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::size_t m_buttonCount { 0U };

    template <class State>
    void AddButton(std::string const& textString)
    {
        int const indexX = static_cast<int>(m_buttonCount) / 11;
        int const indexY = m_buttonCount % 11;
        float const posX
            = detail::buttonOffsetX + indexX * (detail::buttonSizeX + detail::buttonMarginX);
        float const posY
            = detail::buttonOffsetY + indexY * (detail::buttonMarginY + detail::buttonSizeY);
        auto const button = std::make_shared<jt::Button>(
            jt::Vector2u { detail::buttonSizeX, detail::buttonSizeY },
            getGame()->gfx().textureManager());
        button->addCallback(
            [this]() { getGame()->getStateManager().switchState(std::make_shared<State>()); });
        auto const text = jt::dh::createText(getGame()->gfx().target(), textString, 12);
        text->setTextAlign(jt::Text::TextAlign::LEFT);
        text->setOrigin(jt::Vector2f { -8, 0 });
        button->setDrawable(text);
        button->setPosition(jt::Vector2f { posX, posY });
        add(std::move(button));

        m_buttonCount++;
    }
};

#endif
