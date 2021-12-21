#include "inventory_list.hpp"
InventoryList::InventoryList(std::weak_ptr<ItemRepository> repo)
{
    m_repository = repo;
    m_equipped["head"] = "";
    m_equipped["torso"] = "";
    m_equipped["hands"] = "";
    m_equipped["weapon"] = "";
    m_equipped["legs"] = "";
    m_equipped["feet"] = "";
}

void InventoryList::addItem(std::string const& refId)
{
    if (m_inventory.count(refId) == 0) {
        m_inventory[refId] = 0;
    }
    m_inventory[refId]++;
}

std::string InventoryList::getAndResetItemToSpawn()
{
    std::string empty { "" };

    std::swap(empty, m_itemToSpawn);
    return empty;
}

std::vector<std::string> InventoryList::getEquippedItems()
{
    std::vector<std::string> equippedItems;
    for (auto const& kvp : m_equipped) {
        if (kvp.second == "") {
            continue;
        }
        equippedItems.push_back(kvp.second);
    }
    return equippedItems;
}
int InventoryList::getTotalWeight()
{
    float weightSum { 0 };
    for (auto kvp : m_equipped) {
        if (kvp.second == "") {
            continue;
        }
        auto const itemReference = m_repository.lock()->getItemReferenceFromString(kvp.second);
        weightSum += itemReference->weight;
    }
    for (auto const& kvp : m_inventory) {
        auto const itemReference = m_repository.lock()->getItemReferenceFromString(kvp.first);
        weightSum += itemReference->weight * kvp.second;
    }
    return static_cast<int>(weightSum);
}

int InventoryList::getMoney() { return m_money; }
void InventoryList::changeMoney(int amount) { m_money += amount; }

void InventoryList::equipItem()
{
    if (m_itemToEquip == "") {
        return;
    }
    auto itemReference = m_repository.lock()->getItemReferenceFromString(m_itemToEquip);
    m_equipped.at(itemReference->equipSlot) = m_itemToEquip;

    m_inventory[m_itemToEquip]--;

    m_itemToEquip = "";
}

void InventoryList::unequipItem()
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

void InventoryList::removeItemToDrop()
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
