#include "inventory_list_imgui.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include "item_reference.hpp"
#include <iostream>

InventoryListImgui::InventoryListImgui(std::weak_ptr<ItemRepository> repo)
    : InventoryList(repo)
{
}

void InventoryListImgui::doUpdate(float const)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::I)) {
        m_drawInventory = !m_drawInventory;
    }
    removeItemToDrop();
    unequipItem();
    equipItem();
}

void InventoryListImgui::doDraw() const
{
    if (!m_drawInventory) {
        return;
    }
    ImGui::SetNextWindowPos(ImVec2 { 400, 0 });

    ImGui::SetNextWindowSize(ImVec2 { 400, 600 });
    ImGui::Begin("Inventory", &m_drawInventory);

    drawEquippedItems();

    ImGui::Separator();
    drawInventoryItems();

    ImGui::End();
}

void InventoryListImgui::drawEquippedItems() const
{
    ImGui::Text("Equipped Items");
    for (auto const& kvp : m_equipped) {
        ImGui::Text("%s", kvp.first.c_str());
        ImGui::SameLine();
        std::string const popupName = "item" + kvp.first;

        std::string const displayName
            = (kvp.second.empty()
                      ? "None"
                      : m_repository.lock()->getItemReferenceFromString(kvp.second)->listName)
            + "##" + kvp.first;

        if (ImGui::Button(displayName.c_str())) {
            ImGui::OpenPopup(popupName.c_str());
        }

        if (ImGui::BeginPopup(popupName.c_str())) {
            if (kvp.second == "") {
                ImGui::Text("Nothing Equipped");
            } else {
                std::string unequipButtonText = "Unequip##" + kvp.second;
                if (ImGui::Selectable(unequipButtonText.c_str())) {
                    m_itemToUnequip = kvp.second;
                }
            }

            auto const possibleItems = getItemReferenceIdsForEquipmentSlot(kvp.first);
            for (auto const& itemReferenceId : possibleItems) {
                if (kvp.second == itemReferenceId) {
                    continue;
                }
                auto itemReference
                    = m_repository.lock()->getItemReferenceFromString(itemReferenceId);
                std::string const itemName = itemReference->listName;
                if (ImGui::Selectable(itemName.c_str())) {
                    if (!kvp.second.empty()) {
                        m_itemToUnequip = kvp.second;
                    }
                    m_itemToEquip = itemReferenceId;
                }
            }

            ImGui::EndPopup();
        }
    }
}
void InventoryListImgui::drawInventoryItems() const
{
    ImGui::BeginChild("Items");
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    ImGui::BeginTable("Inventory", 4, flags);
    ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 16.0f);
    ImGui::TableSetupColumn("Item");
    ImGui::TableSetupColumn("Value");
    ImGui::TableSetupColumn("Weight");
    ImGui::TableHeadersRow();

    for (auto& kvp : m_inventory) {
        if (kvp.second <= 0) {
            continue;
        }
        ImGui::TableNextRow();

        drawSingleItemInInventory(kvp);
    }
    ImGui::EndTable();
    ImGui::EndChild();
}
void InventoryListImgui::drawSingleItemInInventory(
    std::pair<std::string const, int> const& kvp) const
{
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("%i", kvp.second);
    auto const refId = kvp.first;

    auto const itemReference = this->m_repository.lock()->getItemReferenceFromString(refId);

    ImGui::TableSetColumnIndex(1);
    auto const itemName = itemReference->listName;

    std::string const popupName = "item" + itemName;
    if (ImGui::Button(itemName.c_str())) {
        ImGui::OpenPopup(popupName.c_str());
    }
    if (ImGui::BeginPopup(popupName.c_str())) {
        ImGui::Text("Action");
        ImGui::Separator();
        std::string const dropButtonText = "Drop 1##" + itemName;
        if (ImGui::Selectable(dropButtonText.c_str())) {
            m_itemToDrop = refId;
        }
        if (itemReference->equipSlot != "") {

            auto const equippedItemInSlot = m_equipped.at(itemReference->equipSlot);
            if (equippedItemInSlot != refId) {

                std::string const equipButtonText = "Equip##" + itemName;
                if (ImGui::Selectable(equipButtonText.c_str())) {
                    this->m_itemToEquip = refId;
                    this->m_itemToUnequip = equippedItemInSlot;
                }
            }
        }
        ImGui::EndPopup();
    }
    ImGui::TableSetColumnIndex(2);
    ImGui::Text("%.1f (%.1f)", itemReference->value * kvp.second, itemReference->value);
    ImGui::TableSetColumnIndex(3);
    ImGui::Text("%.1f (%.1f)", itemReference->weight * kvp.second, itemReference->weight);
}

std::vector<std::string> InventoryListImgui::getItemReferenceIdsForEquipmentSlot(
    std::string const& slot) const
{
    std::vector<std::string> itemsForSlot {};
    for (auto const& kvp : m_inventory) {
        auto const itemReference = m_repository.lock()->getItemReferenceFromString(kvp.first);
        if (itemReference->equipSlot == slot) {
            itemsForSlot.push_back(kvp.first);
        }
    }
    return itemsForSlot;
}
