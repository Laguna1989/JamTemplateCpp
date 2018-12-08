#include "State2.hpp"
#include "State1.hpp"

void State1::doInternalUpdate(float const /*elapsed*/)
{
	std::cout << "1\n";
	if (getAge() >= 5.0)
	{
		getGame()->switchState(std::make_shared<State2>());
	}
}
