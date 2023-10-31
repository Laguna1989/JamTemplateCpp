#ifndef STRESSTEST_STATE_SELECT_HPP
#define STRESSTEST_STATE_SELECT_HPP

#include <button.hpp>
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_state.hpp>
#include <text.hpp>
#include <memory>

namespace detail {
constexpr float buttonOffsetX = 16;
constexpr float buttonOffsetY = 16;
constexpr float buttonMarginY = 8;
constexpr float buttonMarginX = 8;
constexpr unsigned int buttonSizeX = 100;
constexpr unsigned int buttonSizeY = 20;
constexpr int numberOfButtonsPerColumn = 10;

} // namespace detail

class StateSelect : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
    void onEnter() override;

    std::size_t m_buttonCount { 0u };

    template <class State>
    void AddButton(std::string const& textString)
    {
        int const indexX = static_cast<int>(m_buttonCount) / detail::numberOfButtonsPerColumn;
        int const indexY = m_buttonCount % detail::numberOfButtonsPerColumn;
        float const posX
            = detail::buttonOffsetX + indexX * (detail::buttonSizeX + detail::buttonMarginX);
        float const posY
            = detail::buttonOffsetY + indexY * (detail::buttonMarginY + detail::buttonSizeY);
        auto const button = std::make_shared<jt::Button>(
            jt::Vector2u { detail::buttonSizeX, detail::buttonSizeY }, textureManager());
        button->addCallback(
            [this]() { getGame()->stateManager().switchState(std::make_shared<State>()); });
        auto const text = jt::dh::createText(renderTarget(), textString, 16);
        text->setTextAlign(jt::Text::TextAlign::LEFT);
        text->setOrigin(jt::Vector2f { -6, 1 });
        button->setDrawable(text);
        button->setPosition(jt::Vector2f { posX, posY });
        add(std::move(button));

        m_buttonCount++;
    }
};

#endif
