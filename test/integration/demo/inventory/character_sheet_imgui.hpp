#ifndef JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
#define JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP

#include <game_object.hpp>
#include <inventory/item_repository.hpp>
#include <memory>

class CharacterSheetImgui : public jt::GameObject {
public:
    CharacterSheetImgui(std::weak_ptr<ItemRepository> repo);
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    mutable bool m_drawCharacterSheet { false };

    void setEquippedItems(std::vector<std::string> const& items);

    void setCurrentTemperature(float temp);

private:
    std::weak_ptr<ItemRepository> m_repository;

    std::vector<std::string> m_equippedItems;

    float m_currentTemperature { 0.0f };
};

#endif // JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
