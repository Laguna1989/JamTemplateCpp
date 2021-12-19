#ifndef GUARD_JAMTEMPLATE_INVENTORY_HPP
#define GUARD_JAMTEMPLATE_INVENTORY_HPP

#include "game_object.hpp"
#include "item_reference.hpp"
#include "item_repository.hpp"
#include <map>

class ListInventory : public jt::GameObject {
public:
    ListInventory(std::weak_ptr<ItemRepository> repo);
    void addItem(std::string const& refId);
    // TODO include count
    std::string getAndResetItemToSpawn();

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::map<std::string, int> m_inventory;
    std::weak_ptr<ItemRepository> m_repository;

    mutable bool m_drawInventory { false };

    mutable std::string m_itemToDrop { "" };

    mutable std::string m_itemToUnequip { "" };
    mutable std::string m_itemToEquip { "" };

    // maps equipSlot to itemReferenceId
    std::map<std::string, std::string> m_equipped;

    std::string m_itemToSpawn { "" };

    void removeItemToDrop();
    void drawSingleItemInInventory(std::pair<std::string const, int> const& kvp) const;
    void drawInventoryItems() const;

    std::vector<std::string> getItemReferenceIdsForEquipmentSlot(std::string const& slot) const;
    void drawEquippedItems() const;
    void unequipItem();
    void equipItem();
};

#endif // GUARD_JAMTEMPLATE_INVENTORY_HPP
