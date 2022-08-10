#ifndef JAMTEMPLATE_WORLD_ITEM_HPP
#define JAMTEMPLATE_WORLD_ITEM_HPP

#include <game_object.hpp>
#include <inventory/item_reference.hpp>
#include <sprite.hpp>

class InventoryListImgui;

class WorldItem : public jt::GameObject {
public:
    WorldItem(std::shared_ptr<ItemReference> ref, std::shared_ptr<jt::DrawableInterface> drawable);
    std::shared_ptr<jt::DrawableInterface> getDrawable();

    std::string getRefId() const;

    std::string getName() const override;

private:
    std::shared_ptr<jt::DrawableInterface> m_drawable;

    std::string m_refId;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // JAMTEMPLATE_WORLD_ITEM_HPP
