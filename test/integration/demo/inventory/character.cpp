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
    b2FixtureDef fixtureDef;
    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(12, 12);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);

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
    jt::Vector2f newVelocity { 0.0f, 0.0f };
    float const speed = 85.0f;
    if (keyboard->pressed(jt::KeyCode::D)) {
        newVelocity += jt::Vector2f { speed, 0.0f };
    }
    if (keyboard->pressed(jt::KeyCode::A)) {
        newVelocity += jt::Vector2f { -speed, 0.0f };
    }

    if (keyboard->pressed(jt::KeyCode::W)) {
        newVelocity += jt::Vector2f { 0.0f, -speed };
    }
    if (keyboard->pressed(jt::KeyCode::S)) {
        newVelocity += jt::Vector2f { 0.0f, speed };
    }

    setVelocity(newVelocity);

    m_animation->setPosition(getPosition() - jt::Vector2f { 12, 12 });
    m_animation->update(elapsed);

    if (newVelocity.x > 0) {
        //        m_animation->setScale({ -1.0f, 0.0 });
        //        m_animation->setOffset({ 24, 0 });
    } else {
        //        m_animation->setScale({ 1.0f, 0.0 });
        //        m_animation->setOffset({ 0.0f, 0 });
    }

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
