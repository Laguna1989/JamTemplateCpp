#ifndef JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD

#include <memory>
#include <SFML/Graphics.hpp>

namespace JamTemplate {
	// forward declaration
	class Game;

	class GameObject
	{
	public:
		GameObject() = default;

		virtual  ~GameObject() = default;

		void create()
		{
			std::shared_ptr<Game> g;
			try
			{
				g = getGame();
			}
			catch (std::exception& e)
			{
				std::cerr << "ERROR: Game not set on create!\n" << e.what();
			}
			doCreate();
		}
		
		void update(float const elapsed) 
		{ 
			m_age += elapsed; 
			doUpdate(elapsed);
		};
		void draw() const { doDraw(); };
		float getAge() const { return m_age; }
		void setAge(float t) {m_age = t; }

		void setGameInstance(std::weak_ptr<Game> g) { m_game = g; }
		std::shared_ptr<Game> getGame()
		{
			if (m_game.expired()) throw std::exception(/*"ERROR: Cannot GameObject::getGame():  m_game expired!"*/);
			return m_game.lock();
		}
		// const version of getGame (required for draw functionality)
		std::shared_ptr<Game> getGame() const
		{
			if (m_game.expired()) throw std::exception(/*"ERROR: Cannot GameObject::getGame():  m_game expired!"*/);
			return m_game.lock();
		}

		// kill this game Object (killed/dead game objects will get thrown out of any GameState
		void kill() { m_alive = false; }
		bool isAlive() const { return m_alive; }

	private:
		float m_age {0.0f};
		bool m_alive{ true };	// is used to sort out "dead" game objects;
		std::weak_ptr<Game> m_game;

		virtual void doUpdate(float const elapesed) {};
		virtual void doDraw() const {};
		virtual void doCreate() {};
	};

	using GameObjectPtr = std::shared_ptr<GameObject>;
}
#endif
