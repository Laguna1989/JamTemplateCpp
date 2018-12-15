#ifndef JAMTEMPLATE_TWEENPOSITION_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEENPOSITION_HPP_INCLUDEGUARD


#include "TweenBase.hpp"
#include "Lerp.hpp"

namespace JamTemplate {
	template <class T>
	class TweenPosition : public Tween<T> {
	public:
		// Tween position from valueStart to valueEnd of obj withtin time
		static Tween::Sptr create(std::weak_ptr<T> obj, float time, sf::Vector2f valueStart, sf::Vector2f valueEnd)
		{
			return std::make_shared<TweenPosition>(obj, time, valueStart, valueEnd);
		}

		// Tween position from valueStart to valueEnd of obj withtin time
		TweenPosition(std::weak_ptr<T> obj, float time, sf::Vector2f valueStart, sf::Vector2f valueEnd) : Tween<T>{ obj, time, [this](auto sptr, auto age, auto totalTime)
		{
			auto pos = sptr->getPosition();
			
			float val = age / totalTime;

			pos.x = Lerp::linear(static_cast<float>(m_initialValue.x), static_cast<float>(m_finalValue.x), val);
			pos.y = Lerp::linear(static_cast<float>(m_initialValue.y), static_cast<float>(m_finalValue.y), val);
			
			sptr->setPosition(pos);
			return true;
		} }
		{
			std::shared_ptr<T> sptr = nullptr;
			getObject(sptr);
			m_initialValue = valueStart;
			m_finalValue = valueEnd;
		}
	private:
		sf::Vector2f m_initialValue{ };
		sf::Vector2f m_finalValue  { };
	};
} // namespace JamTemplate

#endif
