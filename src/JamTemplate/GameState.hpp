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
			go->create();
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
		
		void internalUpdate(float elapsed)
		{
			doInternalUpdate(elapsed);
		}


	private:
		/// all objects in the scene
		std::vector<GameObjectPtr> m_objects;

		/// this is used as a level of indirection, 
		/// because objects might add or remove m_objects while iterating over the m_objects vector, 
		/// which invalidates pointers, which leads to crashes
		///
		/// the idea is to not modify m_objects directly when a GameObject is added,
		/// but to place them in this vector first and add them to m_objects, 
		/// once it is safe to do so.
		std::vector<GameObjectPtr> m_objectsToAdd;	
		bool m_hasBeenInitialized{ false };
		void initialize() { m_hasBeenInitialized = true; }

		/// do not override this function in derived states, but override doInternalUpdate
		virtual void doUpdate(float const elapsed) override
		{
			updateObjects(elapsed);
			internalUpdate(elapsed);
		}

		virtual void doInternalUpdate(float elapsed)
		{

		}

		void addNewObjects()
		{
			while (!m_objectsToAdd.empty())
			{
				m_objects.emplace_back(std::move(m_objectsToAdd.back()));
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
