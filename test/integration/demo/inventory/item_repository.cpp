#include "item_repository.hpp"
#include "nlohmann.hpp"
#include <fstream>

std::shared_ptr<WorldItem> ItemRepository::createWorldItem(
    std::shared_ptr<ItemReference> ref, jt::TextureManagerInterface& textureManager)
{
    auto spr = std::make_shared<jt::Sprite>(
        ref->worldItemSpriteFileName, ref->worldItemSpriteRect, textureManager);
    auto worldItem = std::make_shared<WorldItem>(ref, spr);
    return worldItem;
}

void ItemRepository::registerItem(std::shared_ptr<ItemReference> ref) { m_items.push_back(ref); }

std::shared_ptr<ItemReference> ItemRepository::getItemReferenceFromString(
    std::string const& itemRefId)
{
    for (auto const& item : m_items) {
        if (item->referenceId == itemRefId) {
            return item;
        }
    }
    return nullptr;
}
void ItemRepository::loadFromJson(std::string const& fileName)
{
    std::ifstream file { fileName };
    nlohmann::json j;
    file >> j;
    std::vector<ItemReference> items = j;
    m_items.clear();
    for (auto i : items) {
        m_items.emplace_back(std::make_shared<ItemReference>(i));
    }
}
