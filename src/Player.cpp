#include "Player.hpp"
#include "StateGame.hpp"

void Player::shoorArrow()
{
	Player::m_gameState.spawnArrow(getPosition() + sf::Vector2f{24,12});
	m_shootTimer = GP::playerShotTimer();
}
