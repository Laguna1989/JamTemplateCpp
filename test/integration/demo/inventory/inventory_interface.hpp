#ifndef JAMTEMPLATE_INVENTORY_INTERFACE_HPP
#define JAMTEMPLATE_INVENTORY_INTERFACE_HPP

#include <game_object.hpp>
#include <string>
#include <vector>

class InventoryInterface : public jt::GameObject {
public:
    virtual ~InventoryInterface() = default;
    virtual void addItem(std::string const& referenceId) = 0;
    virtual std::string getAndResetItemToSpawn() = 0;
    virtual std::vector<std::string> getEquippedItems() = 0;
    virtual int getTotalWeight() = 0;
    virtual int getMoney() = 0;
    virtual void changeMoney(int amount) = 0;
};

#endif // JAMTEMPLATE_INVENTORY_INTERFACE_HPP
