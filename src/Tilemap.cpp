#include "JamTemplate/Game.hpp"
#include "TileMap.hpp"
#include "StateGame.hpp"

Tilemap::Tilemap()
{
}


void Tilemap::doUpdate(float const elapsed)
{
	for (auto& t : m_tiles)
	{
		t->update(elapsed);
	}
}

void Tilemap::doDraw() const 
{
	for (auto& t : m_tiles)
	{
		t->draw();
	}
}

void Tilemap::doCreate() 
{
	for (int i = 0; i != 50; ++i)
		for (int j = 0; j != 50; ++j)
		{
			std::shared_ptr<Tile> t = std::make_shared<Tile>(i, j);
			t->setGameInstance(getGame());
			t->setBlocked(JamTemplate::Random::getChance());
			t->create();
			if (i == 5 && j > 5 && j < 10)
			{
				t->setTileType(TileType::WALL);
			}
			else
			{
				t->setTileType(TileType::GRASS);
			}
			
			m_tiles.push_back(t);
	}
}
