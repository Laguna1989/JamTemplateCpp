#ifndef JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TRANSFORM_HPP_INCLUDEGUARD

#include <SFML/Graphics.hpp>

namespace JamTemplate {

	class Transform
	{
	public:
		using vt = sf::Vector2f;
		using rt = sf::FloatRect;
		Transform() = default;

		explicit Transform(vt p, vt v = vt{}, vt a = vt{}) : m_pos{ p }, m_vel{ v }, m_acc{ a }
		{
		}

		void updateTransform(float elapsed)
		{
			m_vel += m_acc * elapsed;
			m_pos += m_vel * elapsed;
			std::cout << m_pos.y << std::endl;
			setToBounds();
		}
		void setToBounds()
		{
			if (!m_useBounds) return;
			if (getPosition().x < getBounds().left)
			{
				setPosition({ getBounds().left, getPosition().y });
			}
			if (getPosition().x > getBounds().left + getBounds().width)
			{
				setPosition({ getBounds().left + getBounds().width, getPosition().y });
			}

			if (getPosition().y < getBounds().top)
			{
				setPosition({ getPosition().x, getBounds().top });
			}
			if (getPosition().y > getBounds().top + getBounds().height)
			{
				setPosition({ getPosition().x, getBounds().top + getBounds().height });
			}
		}
		void unsetBounds()
		{
			m_useBounds = false;
		}

		void setPosition(vt const& p) { m_pos = p; }
		void setVelocity(vt const& v) { m_vel = v; }
		void setAcceleration(vt const& a) { m_acc = a; }

		vt getPosition() const { return m_pos; }
		vt getVelocity() const { return m_vel; }
		vt getAcceleration() const { return m_acc; }

		rt getBounds() const { return m_bounds; }
		void setBounds(rt const& r)
		{
			m_useBounds = true;
			m_bounds = r;
		}

	private:
		vt m_pos{};
		vt m_vel{};
		vt m_acc{};

		rt m_bounds{};
		bool m_useBounds = false;
	};
}
#endif