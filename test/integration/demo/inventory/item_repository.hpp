#ifndef JAMTEMPLATE_ITEM_REPOSITORY_HPP
#define JAMTEMPLATE_ITEM_REPOSITORY_HPP

#include <inventory/item_reference.hpp>
#include <inventory/world_item.hpp>
#include <memory>
#include <vector>

class ItemRepository {
public:
    std::shared_ptr<WorldItem> createWorldItem(
        std::shared_ptr<ItemReference> ref, jt::TextureManagerInterface& textureManager);

    void registerItem(std::shared_ptr<ItemReference> ref);

    std::shared_ptr<ItemReference> getItemReferenceFromString(std::string const& itemRefId);

    void loadFromJson(std::string const& fileName);

private:
    std::vector<std::shared_ptr<ItemReference>> m_items;
};

#endif // JAMTEMPLATE_ITEM_REPOSITORY_HPP
