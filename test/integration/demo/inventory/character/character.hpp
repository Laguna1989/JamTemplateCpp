#ifndef GUATD_JAMTEMPLATE_CHARACTER_HPP
#define GUATD_JAMTEMPLATE_CHARACTER_HPP

#include "character_controller_interface.hpp"
#include <animation.hpp>
#include <box2dwrapper/box2d_object.hpp>
#include <game_object.hpp>
#include <inventory/character_sheet_imgui.hpp>
#include <inventory/inventory_list_imgui.hpp>
#include <memory>

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
    std::shared_ptr<InventoryInterface> getInventory() override;

    // TODO make this function take a damage object to handle things like cold or heat
    // damage
    void takeDamage(float damage);

    bool isDead() const;

private:
    std::shared_ptr<jt::Animation> m_animation;
    std::shared_ptr<InventoryInterface> m_inventory;
    std::weak_ptr<ItemRepository> m_repo;
    std::shared_ptr<CharacterSheetInterface> m_charsheet;
    std::shared_ptr<jt::Box2DObject> m_physicsObject;

    std::unique_ptr<CharacterControllerInterface> m_characterController { nullptr };

    float m_currentTemperature { 0.0f };
    float m_temperatureDamageTimer { 0.0f };
    float m_health { 100.0f };
    float m_maxHealth { 100.0f };

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    void handleTemperature(float const elapsed);
    void updateCharsheetValues(float const elapsed);
    void die();
};

#endif // GUATD_JAMTEMPLATE_CHARACTER_HPP
