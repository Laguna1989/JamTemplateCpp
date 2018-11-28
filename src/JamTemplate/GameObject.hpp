#ifndef JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAMEOBJECT_HPP_INCLUDEGUARD

#include <memory>
#include <SFML/Graphics.hpp>


namespace JamTemplate {

	class GameObject
	{
	public:
		GameObject();

		virtual  ~GameObject() = default;
	
		void update(float const elapsed) 
		{ 
			m_age += elapsed; 
			doUpdate(elapsed);
		};
		virtual void draw() const {};
		float getAge() const { return m_age; }

	private:
		float m_age;
		virtual void doUpdate(float const elapesed) = 0;
	};

	using GameObjectPtr = std::shared_ptr<GameObject>;
}
#endif
