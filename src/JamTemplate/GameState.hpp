#ifndef JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAMESTATE_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <numeric>
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
			go->setGameInstance(getGame());
			m_objectsToAdd.push_back(go);
		}
		
		bool hasBeenInitialized() const { return m_hasBeenInitialized; }
	protected:
		void updateObjects(float elapsed)
		{
			cleanUpObjects();
			addNewObjects();

			for (auto& go : m_objects)
			{
				go->update(elapsed);
			}
		}
		


	private:
		std::vector<GameObjectPtr> m_objects;

		// this is used as a level of indirection, because objects might add or remove m_objects while iterating over the m_objects vector, which invalidates pointers, which leads to crashes
		std::vector<GameObjectPtr> m_objectsToAdd;	
		bool m_hasBeenInitialized{ false };
		void initialize() { m_hasBeenInitialized = true; }
		virtual void doUpdate(float const elapsed) override
		{
			updateObjects(elapsed);
		}

		void addNewObjects()
		{
			while (!m_objectsToAdd.empty())
			{
				m_objects.push_back(std::move(m_objectsToAdd.back()));
				m_objectsToAdd.pop_back();
			}
		}
		void cleanUpObjects()
		{
			m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [](GameObjectPtr go) {return !(go->isAlive()); }), m_objects.end());
		}
		

		virtual void doDraw() const override
		{
			for (auto& go : m_objects)
			{
				go->draw();
			}
		};

		virtual void doCreate() {};
	};

	using GameStatePtr = std::shared_ptr<GameState>;
}
#endif