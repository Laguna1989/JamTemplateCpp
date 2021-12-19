#include "list_inventory.hpp"
#include "game_interface.hpp"
#include "imgui.h"

ListInventory::ListInventory(std::weak_ptr<ItemRepository> repo) { m_repository = repo; }

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
}

void ListInventory::removeItemToDrop()
{
    if (m_itemToDrop != "") {
        if (m_inventory.count(m_itemToDrop) == 0) {
            return;
        }
        if (m_inventory[m_itemToDrop] == 0) {
            return;
        }
        m_inventory[m_itemToDrop] = 0;
        m_itemToSpawm = m_itemToDrop;
        m_itemToDrop = "";
    }
}

void ListInventory::doDraw() const
{
    if (m_drawInventory) {
        ImGui::Begin("Inventory", &m_drawInventory);
        ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        ImGui::BeginTable("table1", 5, flags);
        ImGui::TableSetupColumn("Count");
        ImGui::TableSetupColumn("Item");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Weight");
        ImGui::TableSetupColumn("");
        ImGui::TableHeadersRow();

        for (auto& kvp : m_inventory) {
            if (kvp.second <= 0) {
                continue;
            }
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%i", kvp.second);
            auto const refId = kvp.first;

            auto const itemReference = m_repository.lock()->getItemReferenceFromString(refId);

            ImGui::TableSetColumnIndex(1);
            auto const itemName = itemReference->listName;
            // TODO clickable button with actions

            if (ImGui::Button(itemName.c_str())) { }
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.1f (%.1f)", itemReference->value * kvp.second, itemReference->value);
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.1f (%.1f)", itemReference->weight * kvp.second, itemReference->weight);
            ImGui::TableSetColumnIndex(4);
            if (ImGui::Button("Drop")) {
                drop(refId);
            }
        }
        ImGui::EndTable();
        ImGui::End();
    }
}
void ListInventory::drop(std::string const& itemToDrop) const { m_itemToDrop = itemToDrop; }
std::string ListInventory::getItemToSpawn()
{
    std::string empty { "" };
    std::swap(empty, m_itemToSpawm);
    return empty;
}
