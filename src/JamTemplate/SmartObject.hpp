#ifndef JAMTEMPLATE_SMARTOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTOBJECT_HPP_INCLUDEGUARD

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Lerp.hpp"

namespace JamTemplate
{
	class SmartObject
	{
	public:

		using Sptr = std::shared_ptr<SmartObject>;
		
		void draw(std::shared_ptr<sf::RenderTarget> sptr) const
		{
			doDraw(sptr);
			if (m_flashTimer > 0)
			{
				doDrawFlash(sptr);
			}
		}

		void flash(float t, sf::Color col = sf::Color::White)
		{
			m_maxFlashTimer = m_flashTimer = t;
			setFlashColor(col);
		}

		void update(float elapsed)
		{
			updateFlash(elapsed);
			doUpdate(elapsed);
		}

		virtual void setColor(sf::Color const& col) = 0;
		virtual const sf::Color getColor() const = 0;

		virtual void setPosition(sf::Vector2f const& pos) = 0;
		virtual const sf::Vector2f getPosition() const = 0;


	private:

		float m_flashTimer{ -1.0f };
		float m_maxFlashTimer{ -1.0f };

		virtual void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const = 0;
		virtual void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const = 0;

		// overwrite this method:
		// things to take care of:
		//   - make sure flash object and normal object are at the same position
		virtual void doUpdate(float elapsed) = 0;

		virtual sf::Transform const getTransform() const = 0;
		virtual sf::FloatRect getGlobalBounds() const = 0;
		

		virtual void setFlashColor(sf::Color const& col) = 0;
		virtual const sf::Color getFlashColor() const = 0;

		void updateFlash(float elapsed)
		{
			if (m_flashTimer > 0)
			{
				m_flashTimer -= elapsed;
				float a = Lerp::linear(255.0f, 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
				auto col = getFlashColor();
				col.a = static_cast<sf::Uint8>(a);
				setFlashColor(col);
			}
		}
	};
}// namespace JamTemplate

#endif
