
#ifndef JAMTEMPLATE_INVENTORY_CALCULATOR_HPP
#define JAMTEMPLATE_INVENTORY_CALCULATOR_HPP

#include <inventory/item_repository.hpp>
#include <memory>
#include <string>
#include <vector>

int getHeatResistance(std::vector<std::string> const& items, std::weak_ptr<ItemRepository> repo);

#endif // JAMTEMPLATE_INVENTORY_CALCULATOR_HPP
