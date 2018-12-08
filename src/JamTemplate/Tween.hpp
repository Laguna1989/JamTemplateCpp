#ifndef JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Lerp.hpp"

namespace JamTemplate {
	class TweenBase{
	public:
		using Sptr = std::shared_ptr<TweenBase>;
		void cancel() { kill(); }
		void update(float elapsed)
		{
			m_age += elapsed;
			doUpdate(elapsed);
		}
		bool isAlive()
		{
			return m_alive;
		}
		void kill()
		{
			m_alive = false;
		}
	protected:
		
		float getAge() const { return m_age; }
	private:
		float m_age{ 0.0f };
		bool m_alive{true};
		virtual void doUpdate(float elapsed) = 0;
	};

	template <class T>
	class Tween :public TweenBase{
	public:
		Tween(std::weak_ptr<T> obj, std::function<bool(std::shared_ptr<T>, float)> cb) : m_obj{ obj }, m_tweenCallback{cb}
		{
		}
		
	protected:
		void getObject(std::shared_ptr<T>& obj)
		{
			if (m_obj.expired()) {
				cancel();
				obj = nullptr;
				return;
			}
			obj = m_obj.lock();
		}
	private:
		std::weak_ptr<T> m_obj;

		// callback function. If the callback returns false, the tween shall be finished.
		std::function<bool(std::shared_ptr<T>, float)>  m_tweenCallback;
		void doUpdate(float /*elapsed*/)  override
		{
			std::shared_ptr<T> sptr = nullptr;
			getObject(sptr);
			if (!m_tweenCallback(sptr, getAge()))
			{
				cancel();
			}			
		}
	};

	template <class T>
	class TweenAlpha : public Tween<T> {
	public:
		// Tween alpha value from valueStart to valueEnd of obj withtin time
		static Tween::Sptr create(std::weak_ptr<T> obj, float time, sf::Uint8 valueStart, sf::Uint8 valueEnd)
		{
			return std::make_shared<TweenAlpha>(obj, time, valueStart, valueEnd);
		}

		// Tween alpha value from valueStart to valueEnd of obj withtin time
		TweenAlpha(std::weak_ptr<T> obj, float time, sf::Uint8 valueStart, sf::Uint8 valueEnd) : Tween<T>{ obj, [this](auto sptr, auto age)
		{
			auto col = sptr->getColor();
			float alpha = Lerp::linear(m_initialValue, m_finalValue, age / m_totalTime);
			sf::Uint8 a = static_cast<sf::Uint8>(alpha*255.0f);
			col.a = a;
			sptr->setColor(col);

			return (age < m_totalTime);
		} }
		{
			std::shared_ptr<T> sptr = nullptr;
			getObject(sptr);
			m_totalTime = time ;
			m_initialValue = static_cast<float>(valueStart) / 255.0f;
			m_finalValue = static_cast<float>(valueEnd) / 255.0f;
		}
	private:
		float m_totalTime{1.0f};
		float m_initialValue{0.0f};
		float m_finalValue{ 0.0f };
		
	};

} // namespace JamTemplate

#endif
