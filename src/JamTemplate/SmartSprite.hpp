#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "Lerp.hpp"

namespace JamTemplate
{
	class SmartSprite
	{
	public:

		using Sptr = std::shared_ptr<SmartSprite>;

		void loadSprite(std::string fileName) 
		{
			m_sprite = sf::Sprite{ TextureManager::get(fileName) };
			m_flashSprite = sf::Sprite{ TextureManager::get(TextureManager::getFlashName(fileName)) };
		}


		void setPosition(sf::Vector2f pos)
		{
			m_sprite.setPosition(pos);

		}

		sf::Vector2f getPosition() const
		{
			return m_sprite.getPosition();
		}

		void setColor(const sf::Color& col)
		{
			m_sprite.setColor(col);
		}
		const sf::Color getColor() const
		{
			return m_sprite.getColor();
		}

		void draw(std::shared_ptr<sf::RenderTarget> sptr) const
		{
			sptr->draw(m_sprite);
			if (m_flashTimer > 0)
			{
				sptr->draw(m_flashSprite);
			}
		}
		
		void update(float elapsed)
		{
			if (m_flashTimer > 0)
			{
				m_flashSprite.setPosition(getPosition());
				m_flashTimer -= elapsed;
				float a = Lerp::linear(255.0f, 0.0f, 1.0f - (m_flashTimer / m_maxFlashTimer));
				
				auto col = m_flashSprite.getColor();
				col.a = static_cast<sf::Uint8>(a);
				m_flashSprite.setColor(col);
			}
		}
		void flash(float t, sf::Color col = sf::Color::White)
		{
			m_maxFlashTimer = m_flashTimer = t;
			m_flashSprite.setColor(col);
		}

	private:
		sf::Sprite m_sprite;
		sf::Sprite m_flashSprite;

		float m_flashTimer{ -1.0f };
		float m_maxFlashTimer{ -1.0f };
	};
}// namespace JamTemplate

#endif
