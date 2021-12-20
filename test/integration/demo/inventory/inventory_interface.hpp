#ifndef GUARD_JAMTEMPLATE_INVENTORY_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_INVENTORY_INTERFACE_HPP

#include <string>
#include <vector>

class InventoryInterface {
public:
    virtual ~InventoryInterface() = default;
    virtual void addItem(std::string const& referenceId) = 0;
    virtual std::string getAndResetItemToSpawn() = 0;
    virtual std::vector<std::string> getEquippedItems() = 0;
    virtual int getTotalWeight() = 0;
    virtual int getMoney() = 0;
    virtual void changeMoney(int amount) = 0;
};

#endif // GUARD_JAMTEMPLATE_INVENTORY_INTERFACE_HPP
