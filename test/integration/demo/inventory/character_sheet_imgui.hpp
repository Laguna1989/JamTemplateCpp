#ifndef JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
#define JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP

#include <game_object.hpp>
#include <inventory/item_repository.hpp>
#include <memory>

class CharacterSheetInterface : public jt::GameObject {
public:
    virtual ~CharacterSheetInterface() = default;
    virtual void setEquippedItems(std::vector<std::string> const& items) = 0;
    virtual void setCurrentTemperature(float temperature) = 0;
    virtual void setHealth(float current, float max) = 0;
};

class CharacterSheetBase : public CharacterSheetInterface {
public:
    CharacterSheetBase(std::weak_ptr<ItemRepository> repo);
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    void setEquippedItems(std::vector<std::string> const& items) override;

    void setCurrentTemperature(float temp) override;
    void setHealth(float current, float max) override;

protected:
    std::weak_ptr<ItemRepository> m_repository;
    std::vector<std::string> m_equippedItems;
    float m_currentTemperature { 0.0f };
    float m_health { 100.0f };
    float m_maxHealth { 100.0f };
};

class CharacterSheetImgui : public CharacterSheetBase {
public:
    CharacterSheetImgui(std::weak_ptr<ItemRepository> repo);
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

private:
    mutable bool m_drawCharacterSheet { false };
};

#endif // JAMTEMPLATE_CHARACTER_SHEET_IMGUI_HPP
