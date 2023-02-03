#include "character.hpp"
#include <game_interface.hpp>
#include <inventory/character/character_controller_player.hpp>
#include <Box2D/Box2D.h>

PlayerCharacter::PlayerCharacter(
    std::shared_ptr<jt::Box2DWorldInterface> world, std::weak_ptr<ItemRepository> repo)
{
    m_inventory = std::make_shared<InventoryListImgui>(repo);
    m_charsheet = std::make_shared<CharacterSheetImgui>(repo);

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5 * 24, 7 * 24);
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void PlayerCharacter::doCreate()
{
    b2FixtureDef fixtureDef;
    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(8, 11);
    fixtureDef.shape = &boxCollider;
    m_physicsObject->getB2Body()->CreateFixture(&fixtureDef);

    m_animation = std::make_shared<jt::Animation>();
    m_animation->add("assets/test/integration/demo/chars.png", "idle", jt::Vector2u { 24, 24 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 }, 0.25f, textureManager());

    m_animation->play("idle");
    m_animation->setPosition(jt::Vector2f { 5 * 24, 7 * 24 });
    m_animation->setOrigin(jt::OriginMode::CENTER);

    m_inventory->setGameInstance(getGame());
    m_charsheet->setGameInstance(getGame());
    m_characterController
        = std::make_unique<CharacterControllerPlayer>(getGame()->input().keyboard());
}

void PlayerCharacter::doUpdate(float const elapsed)
{
    if (m_characterController) {
        m_characterController->update(*m_physicsObject.get());
    }
    auto const newVelocity = m_physicsObject->getVelocity();
    m_animation->setPosition(m_physicsObject->getPosition());
    m_animation->update(elapsed);

    float xscale = ((newVelocity.x < 0.0f) ? 1.0f : -1.0f);

    m_animation->setScale(jt::Vector2f { xscale, 1.0f });

    m_inventory->update(elapsed);
    m_charsheet->setEquippedItems(m_inventory->getEquippedItems());
    m_charsheet->setCurrentTemperature(m_current_temperature);
    m_charsheet->update(elapsed);
}

void PlayerCharacter::doDraw() const
{
    m_animation->draw(renderTarget());
    m_inventory->draw();
    m_charsheet->draw();
}

std::shared_ptr<InventoryInterface> PlayerCharacter::getInventory() { return m_inventory; }
std::shared_ptr<CharacterSheetImgui> PlayerCharacter::getCharSheet() { return m_charsheet; }
std::shared_ptr<jt::Box2DObject> PlayerCharacter::getBox2DObject() const { return m_physicsObject; }
void PlayerCharacter::setCurrentTemperature(float temp) { m_current_temperature = temp; }
