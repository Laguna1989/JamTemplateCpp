#ifndef JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "GameObject.hpp"

namespace JamTemplate {

	// forward declaration
	class Game;

	class GameState : public GameObject
	{
	public:
		GameState() = default;

		virtual  ~GameState() = default;
	
		void create() { doCreate(); initialize(); };
		
		

		void add(GameObjectPtr go)
		{
			m_objects.push_back(go);
		}
		
		void setGameInstance(std::weak_ptr<Game> gm)
		{
			m_Game = gm;
		}

		bool hasBeenInitialized() const { return m_hasBeenInitialized; }
		

	protected:
		std::weak_ptr<Game> m_Game;
	private:
		std::vector<GameObjectPtr> m_objects;
		bool m_hasBeenInitialized{ false };
		void initialize() { m_hasBeenInitialized = true; }
		virtual void doUpdate(float const elapsed) override
		{
			for (auto& go : m_objects)
			{
				go->update(elapsed);
			}
		};

		virtual void doDraw(sf::RenderTarget& rt) const override
		{
			for (auto& go : m_objects)
			{
				go->draw(rt);
			}
		};

		virtual void doCreate() {};
	};

	using GameStatePtr = std::shared_ptr<GameState>;
}
#endif