#include "Player.hpp"
#include "StateGame.hpp"

void Player::shoorArrow()
{
	Player::m_gameState.spawnArrow(getPosition());
	m_shootTimer = GP::playerShotTimer();
}
