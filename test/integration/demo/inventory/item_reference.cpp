#include "item_reference.hpp"
#include <utility>

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

void from_json(nlohmann::json const& j, jt::Vector2f& vec)
{
    j.at("x").get_to(vec.x);
    j.at("y").get_to(vec.y);
}

} // namespace jt

void from_json(nlohmann::json const& j, ArmorInfo& armor)
{
    j.at("armor").get_to(armor.armor);
    if (j.count("resistanceFire") != 0) {
        j.at("resistanceFire").get_to(armor.resistanceFire);
    }
    if (j.count("resistanceElectric") != 0) {
        j.at("resistanceElectric").get_to(armor.resistanceElectric);
    }
}

void from_json(nlohmann::json const& j, ItemReference& item)
{
    j.at("referenceId").get_to(item.referenceId);
    j.at("listName").get_to(item.listName);
    j.at("weight").get_to(item.weight);
    j.at("value").get_to(item.value);
    j.at("worldItemSpriteFileName").get_to(item.worldItemSpriteFileName);
    j.at("worldItemSpriteRect").get_to(item.worldItemSpriteRect);
    // optional json entries
    if (j.count("worldItemOffset") != 0) {
        j.at("worldItemOffset").get_to(item.worldItemOffset);
    }
    if (j.count("equipSlot") != 0) {
        j.at("equipSlot").get_to(item.equipSlot);
        if (j.count("armor") != 0) {
            item.armor = ArmorInfo {};
            j.at("armor").get_to(item.armor.value());
        }
    }
}
