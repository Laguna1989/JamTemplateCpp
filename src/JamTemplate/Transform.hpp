#ifndef JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>

namespace JamTemplate {

	class Transform
	{
	public:
		using vt = sf::Vector2f;
		Transform() = default;

		explicit Transform(vt p, vt v = vt{}, vt a = vt{}) : m_pos{ p }, m_vel{ v }, m_acc{ a }
		{
		}

		void updateTransform(float elapsed)
		{
			m_vel += m_acc * elapsed;
			m_pos += m_vel * elapsed;
		}

		void setPosition(vt const& p) { m_pos = p; }
		void setVelocity(vt const& v) { m_vel = v; }
		void setAcceleration(vt const& a) { m_acc = a; }

		sf::Vector2f getPosition() const { return m_pos; }
		sf::Vector2f getVelocity() const { return m_vel; }
		sf::Vector2f getAcceleration() const { return m_acc; }

	private:
		vt m_pos{};
		vt m_vel{};
		vt m_acc{};
	};
}
#endif