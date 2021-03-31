#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include "GameState.hpp"

namespace jt {

class SmartText;
class SmartShape;
class SmartAnimation;
class SmartSprite;

} // namespace jt

class StateMenu : public jt::GameState {
public:
    StateMenu();

    void setScore(int s) {};

private:
    std::shared_ptr<jt::SmartShape> m_background;

    std::shared_ptr<jt::SmartText> m_text_Title;
    std::shared_ptr<jt::SmartText> m_test_Explanation;
    std::shared_ptr<jt::SmartText> m_text_Credits;

    std::shared_ptr<jt::SmartShape> m_overlay;
    std::shared_ptr<jt::SmartSprite> m_vignette;

    bool m_started { false };

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void checkForTransitionToStateGame();
    void startTransitionToStateGame();
    void doInternalDraw() const override;
};

#endif
