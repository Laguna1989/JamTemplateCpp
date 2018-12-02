#ifndef JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TWEEN_HPP_INCLUDEGUARD

#include <functional>

namespace JamTemplate {

	class Tween {
	public:
		// TODO: think about tween class
		Tween() = delete;

	private:
		std::function<void(void)>  m_tweenCallback;
	};

} // namespace JamTemplate

#endif
