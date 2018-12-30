#include "StateMovement.hpp"
#include "State1.hpp"

void StateMovement::doInternalUpdate(float const /*elapsed*/)  {
	//std::cout << "2\n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
	{
		getGame()->switchState(std::make_shared<State1>());
	}
}
