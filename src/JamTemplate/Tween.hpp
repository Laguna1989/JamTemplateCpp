#ifndef JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD

#include <functional>
#include <memory>

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
		float m_age{ 0.0f };
		
	private:
		bool m_alive{true};
		virtual void doUpdate(float elapsed) = 0;
	};

	template <class T>
	class Tween :public TweenBase{
	public:
		Tween(std::weak_ptr<T> obj, std::function<bool(std::shared_ptr<T>, float)> cb) : m_obj{ obj }, m_tweenCallback{cb}
		{
		}
		
	private:
		std::weak_ptr<T> m_obj;
		std::function<void(std::shared_ptr<T>, float)>  m_tweenCallback;
		void doUpdate(float /*elapsed*/)  override
		{
			if (m_obj.expired()) {
				cancel();
				return;
			}
			auto sptr = m_obj.lock();
			m_tweenCallback(sptr, m_age);
			
		}

	};

} // namespace JamTemplate

#endif
