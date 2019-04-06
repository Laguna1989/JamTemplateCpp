#ifndef GAME_TILEMAP_HPP_INCLUDEGUARD
#define GAME_TILEMAP_HPP_INCLUDEGUARD

#include <vector>
#include"Tile.hpp"
#include "JamTemplate/GameObject.hpp"

class StateGame;

class Tilemap : public JamTemplate::GameObject {
public:
	Tilemap();

private:

	void doUpdate(float const elapsed) override;

	void doDraw() const override;

	void doCreate() override;

	std::vector<std::shared_ptr<Tile>> m_tiles;

	std::shared_ptr<sf::RenderTexture> m_renderTexture;
};

#endif
