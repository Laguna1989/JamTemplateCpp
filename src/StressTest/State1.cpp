#include "State2.hpp"
#include "State1.hpp"

#include "../JamTemplate/Timer.hpp"
#include "../JamTemplate/TweenAlpha.hpp"
#include "../JamTemplate/TweenColor.hpp"
#include "../JamTemplate/TweenScale.hpp"

void State1::doInternalUpdate(float const /*elapsed*/)
{
	unsigned int N = 1;
	for (unsigned int i = 0; i != N; ++i)
	{
		Object::Sptr bp = std::make_shared<Object>();
		add(bp);
		using JamTemplate::Timer;
		Timer::Sptr t = std::make_shared<Timer>(JamTemplate::Random::getFloat(0.125, 3), [bp]() {bp->Flash();});
		add(t);

		auto tw = JamTemplate::TweenAlpha<JamTemplate::Animation>::create(bp->getAnimation(), 0.1f, 255, 0);
		tw->setStartDelay(0.75f);
		add(tw);
		
		auto tw2 = JamTemplate::TweenColor<JamTemplate::Animation>::create(bp->getAnimation(), 0.4f, sf::Color::White, sf::Color::Red);
		tw2->setStartDelay(0.4f);
		add(tw2);

		auto tw3 = JamTemplate::TweenScale<JamTemplate::Animation>::create(bp->getAnimation(), 0.9f, sf::Vector2f{ 1,1 }, sf::Vector2f{ 3,3 });
		add(tw3);
		
	}


	if (getAge() >= 5.0)
	{
		getGame()->switchState(std::make_shared<State2>());
	}
}
