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

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    std::map<std::string, int> m_inventory;
    std::weak_ptr<ItemRepository> m_repository;

    mutable bool m_drawInventory { false };
};

#endif // GUARD_JAMTEMPLATE_INVENTORY_HPP
