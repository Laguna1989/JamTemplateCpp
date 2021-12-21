#ifndef GUARD_JAMTEMPLATE_INVENTORY_LIST_IMGUI_HPP
#define GUARD_JAMTEMPLATE_INVENTORY_LIST_IMGUI_HPP

#include "game_object.hpp"
#include "inventory_list.hpp"
#include "item_repository.hpp"
#include <memory>
#include <vector>

class InventoryListImgui : public InventoryList, public jt::GameObject {
public:
    InventoryListImgui(std::weak_ptr<ItemRepository> repo);

private:
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    mutable bool m_drawInventory { false };

    void drawSingleItemInInventory(std::pair<std::string const, int> const& kvp) const;
    void drawInventoryItems() const;
    void drawEquippedItems() const;

    // TODO might be a candidate to pull into the base class InventoryList
    std::vector<std::string> getItemReferenceIdsForEquipmentSlot(std::string const& slot) const;
};

#endif // GUARD_JAMTEMPLATE_INVENTORY_LIST_IMGUI_HPP
