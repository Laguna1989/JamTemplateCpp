#include "Player.hpp"
#include "StateGame.hpp"

void Player::doDraw() const
{
	getGame()->getRenderTarget()->draw(rect);
}

void Player::shoorArrow()
{
	Player::m_gameState.spawnArrow(getPosition());
}