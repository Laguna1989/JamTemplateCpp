#ifndef GAME_TILE_HPP_INCLUDEGUARD
#define GAME_TILE_HPP_INCLUDEGUARD

#include "JamTemplate/GameObject.hpp"

namespace JamTemplate
{
	class SmartShape;
	class SmartSprite;
}

enum class TileType
{
	GRASS,
	WALL
};

class Tile : public JamTemplate::GameObject {
public:

	Tile(int tx, int ty);

	void setBlocked(bool blocked);
	inline bool getBlocked() { return m_blocked; }

	inline int getTilePosX() { return m_tx; }
	inline int getTilePosY() { return m_ty; }

	void setTileType(TileType tt) { m_tileType = tt; loadGraphic(); }

private:
	void doUpdate(float const elapsed) override;

	void doDraw() const override;

	void doCreate() override;
	void loadGraphic();

	int m_tx, m_ty;
	bool m_blocked{ false };
	
	std::shared_ptr<JamTemplate::SmartSprite> m_spr;

	TileType m_tileType;
};

#endif
