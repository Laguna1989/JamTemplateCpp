#include "StateTween.hpp"
#include "State1.hpp"

void StateTween::doInternalUpdate(float const /*elapsed*/)  {
	//std::cout << "2\n";
	if (getAge() >= 10.0f)
	{
		getGame()->switchState(std::make_shared<State1>());
	}
}
