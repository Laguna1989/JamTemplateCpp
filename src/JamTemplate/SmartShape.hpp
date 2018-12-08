#ifndef JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTSHAPE_HPP_INCLUDEGUARD

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

namespace JamTemplate
{
	class SmartShape
	{
	public:

		using Sptr = std::shared_ptr<SmartShape>;
	
		void makeRect(sf::Vector2f size)
		{
			m_shape = std::make_shared<sf::RectangleShape>(size);
		}
		
		void draw(std::shared_ptr<sf::RenderTarget> sptr) const
		{
			sptr->draw(*m_shape);
		}

		void setColor(sf::Color const& col)
		{
			m_shape->setFillColor(col);
		}
		const sf::Color getColor() const
		{
			return m_shape->getFillColor();
		}

	private:
		std::shared_ptr<sf::Shape> m_shape = nullptr;

	};
}// namespace JamTemplate

#endif
