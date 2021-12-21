#ifndef GUARD_JAMTEMPLATE_WORLD_ITEM_HPP
#define GUARD_JAMTEMPLATE_WORLD_ITEM_HPP

#include "game_object.hpp"
#include "item_reference.hpp"
#include "sprite.hpp"

class InventoryListImgui;

class WorldItem : public jt::GameObject {
public:
    WorldItem(std::shared_ptr<ItemReference> ref, std::shared_ptr<jt::DrawableInterface> drawable);
    std::shared_ptr<jt::DrawableInterface> getDrawable();

    std::string getRefId() const;

private:
    std::shared_ptr<jt::DrawableInterface> m_drawable;

    std::string m_refId;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_WORLD_ITEM_HPP
