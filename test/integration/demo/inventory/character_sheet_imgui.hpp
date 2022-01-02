#ifndef GUARD_JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
#define GUARD_JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP

#include "game_object.hpp"
#include "item_repository.hpp"
#include <memory>

class CharacterSheetImgui : public jt::GameObject {
public:
    CharacterSheetImgui(std::weak_ptr<ItemRepository> repo);
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    mutable bool m_drawCharacterSheet { false };

    void setEquippedItems(std::vector<std::string> const& items);

private:
    std::weak_ptr<ItemRepository> m_repository;

    std::vector<std::string> m_equippedItems;
};

#endif // GUARD_JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
