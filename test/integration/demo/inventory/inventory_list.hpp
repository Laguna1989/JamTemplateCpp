#ifndef GUARD_JAMTEMPLATE_INVENTORY_LIST_HPP
#define GUARD_JAMTEMPLATE_INVENTORY_LIST_HPP

#include "inventory_interface.hpp"
#include "item_repository.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

class InventoryList : public InventoryInterface {
public:
    InventoryList(std::weak_ptr<ItemRepository> repo);

    void addItem(std::string const& refId) override;
    std::string getAndResetItemToSpawn() override;

    std::vector<std::string> getEquippedItems() override;

    int getTotalWeight() override;
    int getMoney() override;
    void changeMoney(int amount) override;

protected:
    std::map<std::string, int> m_inventory;
    std::weak_ptr<ItemRepository> m_repository;
    // maps equipSlot to itemReferenceId
    std::map<std::string, std::string> m_equipped;
    std::string m_itemToSpawn { "" };

    int m_money { 0 };

    // need to be mutable, as the variables will be changed from within the const draw function
    mutable std::string m_itemToUnequip { "" };
    mutable std::string m_itemToEquip { "" };
    mutable std::string m_itemToDrop { "" };

    void removeItemToDrop();
    void unequipItem();
    void equipItem();
};

#endif // GUARD_JAMTEMPLATE_INVENTORY_LIST_HPP
