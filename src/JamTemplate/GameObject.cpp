#include <iostream>
#include "GameObject.hpp"

namespace JamTemplate {

	GameObject::GameObject() : m_age {0.0f}
	{
		std::cout << "I am alive!\n";
	}
}