#include "State2.hpp"
#include "State1.hpp"

void State2::doInternalUpdate(float const /*elapsed*/)  {
	//std::cout << "2\n";
	if (getAge() >= 35.0)
	{
		getGame()->switchState(std::make_shared<State1>());
	}

	float cutoffDistance = 10;

	sf::Vector2f centerPos{};
	for (auto const& o : *m_SwarmObjects)
	{
		centerPos += o.lock()->getPosition();
	}
	centerPos /= static_cast<float>(m_SwarmObjects->size());

	for (size_t i = 0; i != m_SwarmObjects->size(); ++i)
	{
		auto o1 = m_SwarmObjects->at(i).lock();
		sf::Vector2f SummedUpDir{};
		float lc = JamTemplate::MathHelper::length(centerPos - o1->getPosition());
		SummedUpDir += (centerPos - o1->getPosition())/lc * 1000.0f / static_cast<float>(m_SwarmObjects->size());
		for (size_t j = 0; j != m_SwarmObjects->size(); ++j)
		{
			if (i == j) continue;

			auto o2 = m_SwarmObjects->at(j).lock();
			sf::Vector2f d = o2->getPosition() - o1->getPosition();
			float l = JamTemplate::MathHelper::length(d);
			if (l > 2 * cutoffDistance) continue;
				SummedUpDir += o2->getVelocity() * 0.09f * o2->getSwarmWeight()/o1->getSwarmWeight();

			if (l > cutoffDistance) continue;
			if (l < 1) l = 1;
			SummedUpDir -= d / l / l * 500.0f;
		}
		float l = JamTemplate::MathHelper::length(SummedUpDir);
		if (l > 4)
		{
			//std::cout << i << " " << l << std::endl;
		}

		o1->setVelocity(SummedUpDir);
	}

}
