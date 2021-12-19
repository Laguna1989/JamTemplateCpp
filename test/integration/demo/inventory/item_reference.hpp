#ifndef GUARD_JAMTEMPLATE_ITEM_HPP
#define GUARD_JAMTEMPLATE_ITEM_HPP

#include "nlohmann.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <string>

struct ItemReference {
    std::string referenceId { "" };
    std::string worldItemSpriteFileName { "" };
    jt::Recti worldItemSpriteRect { 0, 0, 0, 0 };
    jt::Vector2f worldItemOffset { 0.0f, 0.0f };
    std::string listName;
    float value { 0.0f };
    float weight { 1.0f };
    std::string equipSlot { "" };
};

bool operator<(ItemReference const& lhs, ItemReference const& rhs);

void from_json(const nlohmann::json& j, ItemReference& item);

#endif // GUARD_JAMTEMPLATE_ITEM_HPP
