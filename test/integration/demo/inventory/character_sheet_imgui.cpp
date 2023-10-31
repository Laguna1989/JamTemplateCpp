#include "character_sheet_imgui.hpp"
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <imgui.h>

CharacterSheetBase::CharacterSheetBase(std::weak_ptr<ItemRepository> repo)
    : m_repository { repo }
{
}

void CharacterSheetBase::doUpdate(float const /*elapsed*/) { }
void CharacterSheetBase::doDraw() const { }

void CharacterSheetBase::setEquippedItems(std::vector<std::string> const& items)
{
    m_equippedItems = items;
}

void CharacterSheetBase::setCurrentTemperature(float temp) { m_currentTemperature = temp; }
void CharacterSheetBase::setHealth(float current, float max)
{
    m_health = current;
    m_maxHealth = max;
}

CharacterSheetImgui::CharacterSheetImgui(std::weak_ptr<ItemRepository> repo)
    : CharacterSheetBase(repo)
{
}

void CharacterSheetImgui::doUpdate(float const /*elapsed*/)
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
    ImGui::Begin("PlayerCharacter", &m_drawCharacterSheet);

    ImGui::Text("Health: %s / %s",
        jt::MathHelper::floatToStringWithXDecimalDigits(m_health, 0).c_str(),
        jt::MathHelper::floatToStringWithXDecimalDigits(m_maxHealth, 0).c_str());

    int totalArmor = 0;
    int totalResistanceElectric = 0;
    int totalResistanceHeat = 0;
    auto itemRepository = m_repository.lock();
    for (auto const& itemRef : m_equippedItems) {
        auto const armor_optional = itemRepository->getItemReferenceFromString(itemRef)->armor;
        if (!armor_optional.has_value()) {
            continue;
        }

        auto const armor = armor_optional.value();
        totalArmor += armor.armor;
        totalResistanceHeat += armor.resistanceHeat;
        totalResistanceElectric += armor.resistanceElectric;
    }

    ImGui::Text("TotalArmor: %s", std::to_string(totalArmor).c_str());
    ImGui::Text("Heat: %s", std::to_string(totalResistanceHeat).c_str());
    ImGui::Text("Electric: %s", std::to_string(totalResistanceElectric).c_str());
    ImGui::Separator();
    ImGui::Text("Temperature: %s",
        jt::MathHelper::floatToStringWithXDecimalDigits(m_currentTemperature, 2).c_str());
    ImGui::End();
}
