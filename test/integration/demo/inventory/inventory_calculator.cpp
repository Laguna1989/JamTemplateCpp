
#include "inventory_calculator.hpp"
int getHeatResistance(std::vector<std::string> const& items, std::weak_ptr<ItemRepository> repo)
{
    int totalResistanceHeat = 0;
    auto itemRepository = repo.lock();
    for (auto const& itemRef : items) {
        auto const armor_optional = itemRepository->getItemReferenceFromString(itemRef)->armor;
        if (!armor_optional.has_value()) {
            continue;
        }

        auto const armor = armor_optional.value();
        totalResistanceHeat += armor.resistanceHeat;
    }
    return totalResistanceHeat;
}
