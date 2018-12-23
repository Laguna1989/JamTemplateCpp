#include "StateTween.hpp"
#include "State1.hpp"

void StateTween::doInternalUpdate(float const /*elapsed*/)  
{
	
	if (getAge() >= 10.0f)
	{
		getGame()->switchState(std::make_shared<State1>());
	}
}
