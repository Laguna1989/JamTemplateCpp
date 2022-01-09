#ifndef GUATD_JAMTEMPLATE_CHARACTER_HPP
#define GUATD_JAMTEMPLATE_CHARACTER_HPP

#include "animation.hpp"
#include "character_sheet_imgui.hpp"
#include "game_object.hpp"
#include "inventory_list_imgui.hpp"
#include <memory>

class Character : public jt::GameObject {
public:
    virtual std::shared_ptr<InventoryInterface> getInventory() = 0;
    virtual std::shared_ptr<CharacterSheetImgui> getCharSheet() = 0;
};

class PlayerCharacter : public Character {
public:
    PlayerCharacter(std::weak_ptr<ItemRepository> repository);

private:
    std::shared_ptr<jt::Animation> m_animation;
    std::shared_ptr<InventoryListImgui> m_inventory;
    std::shared_ptr<CharacterSheetImgui> m_charsheet;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

public:
    std::shared_ptr<InventoryInterface> getInventory() override;
    std::shared_ptr<CharacterSheetImgui> getCharSheet() override;
};

#endif // GUATD_JAMTEMPLATE_CHARACTER_HPP
