#ifndef GUARD_JAMTEMPLATE_ITEM_HPP
#define GUARD_JAMTEMPLATE_ITEM_HPP

#include "nlohmann.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <optional>
#include <string>

struct ArmorInfo {
    int armor { 0 };
    int resistanceFire { 0 };
    int resistanceElectric { 0 };
    // more specialized armor values
};

struct ItemReference {
    std::string referenceId { "" };
    std::string worldItemSpriteFileName { "" };
    jt::Recti worldItemSpriteRect { 0, 0, 0, 0 };
    jt::Vector2f worldItemOffset { 0.0f, 0.0f };
    std::string listName;
    float value { 0.0f };
    float weight { 1.0f };
    std::string equipSlot { "" };
    std::optional<ArmorInfo> armor;
};

bool operator<(ItemReference const& lhs, ItemReference const& rhs);

void from_json(const nlohmann::json& j, ItemReference& item);
void from_json(const nlohmann::json& j, ArmorInfo& armor);

#endif // GUARD_JAMTEMPLATE_ITEM_HPP
