#ifndef GUATD_JAMTEMPLATE_CHARACTER_HPP
#define GUATD_JAMTEMPLATE_CHARACTER_HPP

#include "character_controller_interface.hpp"
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
};

class Character : public CharacterInterface, public jt::GameObject {
public:
    Character(std::shared_ptr<jt::Box2DWorldInterface> world,
        std::weak_ptr<ItemRepository> repository,
        std::unique_ptr<CharacterControllerInterface>&& controller, jt::Vector2f const& pos,
        bool isPlayer = false);

    std::shared_ptr<jt::Box2DObject> getBox2DObject() const;

    void setCurrentTemperature(float temp);

private:
    std::shared_ptr<jt::Animation> m_animation;
    std::shared_ptr<InventoryInterface> m_inventory;
    std::shared_ptr<CharacterSheetInterface> m_charsheet;
    std::shared_ptr<jt::Box2DObject> m_physicsObject;

    std::unique_ptr<CharacterControllerInterface> m_characterController { nullptr };
    float m_current_temperature { 0.0f };

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

public:
    std::shared_ptr<InventoryInterface> getInventory() override;
};

#endif // GUATD_JAMTEMPLATE_CHARACTER_HPP
