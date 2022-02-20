#include "character.hpp"
#include "game_interface.hpp"

PlayerCharacter::PlayerCharacter(std::shared_ptr<jt::Box2DWorldInterface> world,
    b2BodyDef const* def, std::weak_ptr<ItemRepository> repo)
    : jt::Box2DObject { world, def }
{
    m_inventory = std::make_shared<InventoryListImgui>(repo);
    m_charsheet = std::make_shared<CharacterSheetImgui>(repo);
}

void PlayerCharacter::doCreate()
{
    m_animation = std::make_shared<jt::Animation>();
    m_animation->add("assets/demos/inventory/chars.png", "idle", jt::Vector2u { 24, 24 }, { 0, 1 },
        0.2f, getGame()->gfx().textureManager());

    m_animation->play("idle");
    m_animation->setPosition(jt::Vector2f { 5 * 24, 7 * 24 });

    m_inventory->setGameInstance(getGame());
    m_charsheet->setGameInstance(getGame());
}

void PlayerCharacter::doUpdate(float const elapsed)
{
    auto keyboard = getGame()->input().keyboard();
    setVelocity(jt::Vector2f { 0.0f, 0.0f });
    if (keyboard->pressed(jt::KeyCode::D)) {
        setVelocity(jt::Vector2f { 20.0f, 0.0f });
    } else if (keyboard->pressed(jt::KeyCode::A)) {
        setVelocity(jt::Vector2f { -20.0f, 0.0f });
    }
    m_animation->setPosition(getPosition());
    m_animation->update(elapsed);

    m_inventory->update(elapsed);
    m_charsheet->update(elapsed);
    m_charsheet->setEquippedItems(m_inventory->getEquippedItems());
}
void PlayerCharacter::doDraw() const
{
    m_animation->draw(getGame()->gfx().target());
    m_inventory->draw();
    m_charsheet->draw();
}

std::shared_ptr<InventoryInterface> PlayerCharacter::getInventory() { return m_inventory; }
std::shared_ptr<CharacterSheetImgui> PlayerCharacter::getCharSheet() { return m_charsheet; }
