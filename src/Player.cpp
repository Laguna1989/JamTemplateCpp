#include "Player.hpp"
#include "StateGame.hpp"

void Player::doDraw() const
{
	getGame()->getRenderTarget()->draw(m_rect);
}

void Player::shoorArrow()
{
	Player::m_gameState.spawnArrow(getPosition());
	m_shootTimer = 0.5;
}