#include "character.hpp"
#include <game_interface.hpp>
#include <inventory/inventory_calculator.hpp>
#include <Box2D/Box2D.h>

Character::Character(std::shared_ptr<jt::Box2DWorldInterface> world,
    std::weak_ptr<ItemRepository> repo, std::unique_ptr<CharacterControllerInterface>&& controller,
    jt::Vector2f const& pos, bool isPlayer)
    : m_repo { repo }
    , m_characterController { std::move(controller) }

{
    // TODO pass in via DI and then create a factory
    if (isPlayer) {
        m_inventory = std::make_shared<InventoryListImgui>(repo);
        m_charsheet = std::make_shared<CharacterSheetImgui>(repo);
    } else {
        m_inventory = std::make_shared<InventoryList>(repo);
        m_charsheet = std::make_shared<CharacterSheetBase>(repo);
    }

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    m_physicsObject = std::make_shared<jt::Box2DObject>(world, &bodyDef);
}

void Character::doCreate()
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
    m_animation->setZ(2);
    m_inventory->setGameInstance(getGame());
    m_charsheet->setGameInstance(getGame());
}

void Character::doUpdate(float const elapsed)
{
    m_animation->setPosition(m_physicsObject->getPosition());
    m_animation->update(elapsed);
    if (isDead()) {
        return;
    }
    if (m_characterController) {
        m_characterController->update(*m_physicsObject.get());
    }
    auto const newVelocity = m_physicsObject->getVelocity();

    float xscale = ((newVelocity.x < 0.0f) ? 1.0f : -1.0f);
    // TODO for web there seems to be some offset
    m_animation->setScale(jt::Vector2f { xscale, 1.0f });

    m_inventory->update(elapsed);
    handleTemperature(elapsed);
    updateCharsheetValues(elapsed);
}

void Character::handleTemperature(float elapsed)
{
    float const heatResistance
        = static_cast<float>(getHeatResistance(m_inventory->getEquippedItems(), m_repo));

    auto const minTemperature = -15 - heatResistance;
    auto const maxTemperature = 40 + heatResistance;
    if (m_currentTemperature > minTemperature && m_currentTemperature < maxTemperature) {
        return;
    }
    m_temperatureDamageTimer += elapsed;
    auto diff = 0.0f;
    if (m_currentTemperature < minTemperature) {
        diff = std::abs(minTemperature - m_currentTemperature);

    } else if (m_currentTemperature > maxTemperature) {
        diff = std::abs(maxTemperature - m_currentTemperature);
    }
    if (m_temperatureDamageTimer >= 1) {
        m_temperatureDamageTimer = 0.0f;
        auto const damagePerSecond = diff / 10.0f;
        takeDamage(damagePerSecond);
    }
}

void Character::updateCharsheetValues(float const elapsed)
{
    m_charsheet->setEquippedItems(m_inventory->getEquippedItems());
    // TODO could be done via observer pattern
    m_charsheet->setCurrentTemperature(m_currentTemperature);
    m_charsheet->setHealth(m_health, m_maxHealth);
    m_charsheet->update(elapsed);
}

void Character::doDraw() const
{
    m_animation->draw(renderTarget());
    m_inventory->draw();
    m_charsheet->draw();
}

std::shared_ptr<InventoryInterface> Character::getInventory() { return m_inventory; }

std::shared_ptr<jt::Box2DObject> Character::getBox2DObject() const { return m_physicsObject; }

void Character::setCurrentTemperature(float temp) { m_currentTemperature = temp; }

void Character::takeDamage(float damage)
{
    if (m_health <= 0.0f) {
        // already dead
        return;
    }
    m_health -= damage;
    m_animation->flash(0.25f, jt::colors::Red);
    if (m_health <= 0) {
        m_health = 0.0f;
        die();
    }
}

void Character::die()
{
    m_animation->setRotation(90.0f);
    m_animation->setColor(jt::Color { 100, 100, 100 });
    m_physicsObject->getB2Body()->SetActive(false);
}

bool Character::isDead() const { return m_health <= 0; }
