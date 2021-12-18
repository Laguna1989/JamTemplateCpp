#include "item_reference.hpp"

bool operator<(ItemReference const& lhs, ItemReference const& rhs)
{
    return lhs.referenceId < rhs.referenceId;
}

namespace jt {

void from_json(nlohmann::json const& j, jt::Recti& rect)
{
    j.at("left").get_to(rect.left);
    j.at("top").get_to(rect.top);
    j.at("width").get_to(rect.width);
    j.at("height").get_to(rect.height);
}
} // namespace jt

void from_json(nlohmann::json const& j, ItemReference& item)
{
    j.at("referenceId").get_to(item.referenceId);
    j.at("listName").get_to(item.listName);
    j.at("weight").get_to(item.weight);
    j.at("value").get_to(item.value);
    j.at("worldItemSpriteFileName").get_to(item.worldItemSpriteFileName);
    j.at("worldItemSpriteRect").get_to(item.worldItemSpriteRect);
}
