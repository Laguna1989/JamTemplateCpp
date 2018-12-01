#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

class GP
{
public:
	GP() = delete;
	static float playerMovementSpeed() { return 40; }
	static float playerShotTimer() { return 0.6f; }
	static float shotMovementSpeed() { return 240; }
	static float balloonMoveSpeed() { return 45; }
	static float balloonSpawnTime() { return 1.75f; }
};

#endif
