#ifndef GUATD_JAMTEMPLATE_CHARACTER_HPP
#define GUATD_JAMTEMPLATE_CHARACTER_HPP

#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <inventory/character_sheet_imgui.hpp>
#include <inventory/inventory_list_imgui.hpp>
#include <memory>

// TODO replace with character class from Alakajam
class CharacterInterface {
public:
    virtual std::shared_ptr<InventoryInterface> getInventory() = 0;
    virtual std::shared_ptr<CharacterSheetImgui> getCharSheet() = 0;
};

class PlayerCharacter : public CharacterInterface, public jt::GameObject {
public:
    PlayerCharacter(std::shared_ptr<jt::Box2DWorldInterface> world,
        std::weak_ptr<ItemRepository> repository);

    std::shared_ptr<jt::Box2DObject> getBox2DObject() const;

private:
    std::shared_ptr<jt::Animation> m_animation;
    std::shared_ptr<InventoryListImgui> m_inventory;
    std::shared_ptr<CharacterSheetImgui> m_charsheet;
    std::shared_ptr<jt::Box2DObject> m_physicsObject;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

public:
    std::shared_ptr<InventoryInterface> getInventory() override;
    std::shared_ptr<CharacterSheetImgui> getCharSheet() override;
};

#endif // GUATD_JAMTEMPLATE_CHARACTER_HPP
