#include "character_sheet_imgui.hpp"
#include "game_interface.hpp"
#include "imgui.h"

CharacterSheetImgui::CharacterSheetImgui(std::weak_ptr<ItemRepository> repo)
    : m_repository { repo }
{
}

void CharacterSheetImgui::doUpdate(float const)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::C)) {
        m_drawCharacterSheet = !m_drawCharacterSheet;
    }
}
void CharacterSheetImgui::doDraw() const
{
    if (!m_drawCharacterSheet) {
        return;
    }
    ImGui::SetNextWindowPos(ImVec2 { 0, 0 });

    ImGui::SetNextWindowSize(ImVec2 { 400, 600 });
    ImGui::Begin("Character", &m_drawCharacterSheet);

    ImGui::End();
}
