#include "list_inventory.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include <iostream>

ListInventory::ListInventory(std::weak_ptr<ItemRepository> repo)
{
    m_repository = repo;
    m_equipped["head"] = "";
    m_equipped["torso"] = "";
    m_equipped["left hand"] = "";
    m_equipped["right hand"] = "";
    m_equipped["legs"] = "";
    m_equipped["feet"] = "";
}

void ListInventory::addItem(std::string const& refId)
{
    if (m_inventory.count(refId) == 0) {
        m_inventory[refId] = 0;
    }
    m_inventory[refId]++;
}

void ListInventory::doCreate() { }

void ListInventory::doUpdate(float const)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::I)) {
        m_drawInventory = !m_drawInventory;
    }
    removeItemToDrop();
    unequipItem();
    equipItem();
}
void ListInventory::equipItem()
{
    if (m_itemToEquip == "") {
        return;
    }
    auto itemReference = m_repository.lock()->getItemReferenceFromString(m_itemToEquip);
    m_equipped.at(itemReference->equipSlot) = m_itemToEquip;

    // TODO might need some rework
    m_inventory[m_itemToEquip]--;

    m_itemToEquip = "";
}

void ListInventory::unequipItem()
{
    if (m_itemToUnequip == "") {
        return;
    }
    for (auto& kvp : m_equipped) {
        if (kvp.second == m_itemToUnequip) {
            addItem(kvp.second);
            kvp.second = "";
            break;
        }
    }
    m_itemToUnequip = "";
}

void ListInventory::removeItemToDrop()
{
    if (m_itemToDrop == "") {
        return;
    }
    if (m_inventory.count(m_itemToDrop) == 0) {
        return;
    }
    if (m_inventory[m_itemToDrop] == 0) {
        return;
    }
    m_inventory[m_itemToDrop]--;
    m_itemToSpawn = m_itemToDrop;
    m_itemToDrop = "";
}

void ListInventory::doDraw() const
{
    if (m_drawInventory) {
        ImGui::Begin("Inventory", &m_drawInventory);

        drawEquippedItems();

        ImGui::Separator();
        drawInventoryItems();

        ImGui::End();
    }
}
void ListInventory::drawEquippedItems() const
{
    ImGui::Text("Equipped Items");
    for (auto const& kvp : m_equipped) {
        ImGui::Text(kvp.first.c_str());
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
void ListInventory::drawInventoryItems() const
{
    // TODO Look into ListClipper
    ImGui::BeginChild("Items");
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    ImGui::BeginTable("Inventory", 4, flags);
    ImGui::TableSetupColumn("Count");
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
void ListInventory::drawSingleItemInInventory(std::pair<std::string const, int> const& kvp) const
{
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("%i", kvp.second);
    auto const refId = kvp.first;

    auto const itemReference = this->m_repository.lock()->getItemReferenceFromString(refId);

    ImGui::TableSetColumnIndex(1);
    auto const itemName = itemReference->listName;
    // TODO clickable button with actions

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

std::string ListInventory::getAndResetItemToSpawn()
{
    std::string empty { "" };

    std::swap(empty, m_itemToSpawn);
    return empty;
}
std::vector<std::string> ListInventory::getItemReferenceIdsForEquipmentSlot(
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
