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
	
		
		virtual void draw() const override 
		{
			for (auto& go : m_objects)
			{
				go->draw();
			}
		};

		void add(GameObjectPtr go)
		{
			m_objects.push_back(go);
		}
		
		void setGameInstance(std::weak_ptr<Game> gm)
		{
			m_Game = gm;
		}

	protected:
		std::weak_ptr<Game> m_Game;
	private:
		std::vector<GameObjectPtr> m_objects;
		
		virtual void doUpdate(float const elapsed) override
		{
			for (auto& go : m_objects)
			{
				go->update(elapsed);
			}
		};

	};

	using GameStatePtr = std::shared_ptr<GameState>;
}
#endif