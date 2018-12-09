#ifndef JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSPRITE_HPP_INCLUDEGUARD

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "SmartObject.hpp"
#include "TextureManager.hpp"


namespace JamTemplate
{
	class SmartSprite : public SmartObject
	{
	public:

		using Sptr = std::shared_ptr<SmartSprite>;

		void loadSprite(std::string fileName) 
		{
			m_sprite = sf::Sprite{ TextureManager::get(fileName) };
			m_flashSprite = sf::Sprite{ TextureManager::get(TextureManager::getFlashName(fileName)) };
		}


		void setPosition(sf::Vector2f const& pos) override
		{
			m_sprite.setPosition(pos);

		}

		const sf::Vector2f getPosition() const override
		{
			return m_sprite.getPosition();
		}

		void setColor(const sf::Color& col) override
		{
			m_sprite.setColor(col);
		}
		const sf::Color getColor() const override
		{
			return m_sprite.getColor();
		}

		void setFlashColor(const sf::Color& col) override
		{
			m_flashSprite.setColor(col);
		}
		const sf::Color getFlashColor() const override
		{
			return m_flashSprite.getColor();
		}

		sf::Transform const getTransform() const override
		{
			return m_sprite.getTransform();
		}

		sf::FloatRect getGlobalBounds() const override
		{
			return m_sprite.getGlobalBounds();
		}
		

	private:
		sf::Sprite m_sprite;
		sf::Sprite m_flashSprite;

		void doUpdate(float /*elapsed*/) override
		{
			m_flashSprite.setPosition(getPosition());
		}

		void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const override
		{
			sptr->draw(m_sprite);
		}

		void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const override
		{
			sptr->draw(m_flashSprite);
		}
	};
}// namespace JamTemplate

#endif
