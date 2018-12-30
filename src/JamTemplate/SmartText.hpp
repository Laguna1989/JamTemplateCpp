#ifndef JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_SMARTTEXT_HPP_INCLUDEGUARD

#include <string>
#include <memory>
#include <exception>

#include <SFML/Graphics.hpp>

#include "SmartObject.hpp"


namespace JamTemplate
{
	class SmartText : public SmartObject
	{
	public:


		using Sptr = std::shared_ptr<SmartText>;

		void loadFont(std::string fontFileName)
		{
			if (!m_font.loadFromFile(fontFileName))
			{
				std::cerr << "cannot load font: " << fontFileName << std::endl;
			}
			m_text = sf::Text{ "", m_font, 8 };
			//m_text.setFont(m_font);
			//m_flashText.setFont(m_font);
		}

		void setCharacterSize(unsigned int cs)
		{
			m_text.setCharacterSize(cs);
		}

		void setText(std::string text)
		{
			m_text.setString(text);
			m_flashText.setString(text);
		}

		void setOutline(float thickness, sf::Color col)
		{
			m_text.setOutlineThickness(thickness);
			m_text.setOutlineColor(col);
		}

		void setPosition(sf::Vector2f const& pos) override
		{
			m_position = pos;
		}

		const sf::Vector2f getPosition() const override
		{
			return m_position;
		}

		void setColor(const sf::Color& col) override
		{
			m_text.setFillColor(col);
		}
		const sf::Color getColor() const override
		{
			return m_text.getFillColor();
		}

		void setFlashColor(const sf::Color& col) override
		{
			m_flashText.setFillColor(col);
		}
		const sf::Color getFlashColor() const override
		{
			return m_flashText.getFillColor();
		}

		virtual sf::Transform const getTransform() const override
		{
			return m_text.getTransform();
		}

		virtual sf::FloatRect getGlobalBounds() const override
		{
			return m_text.getGlobalBounds();
		}
		virtual sf::FloatRect getLocalBounds() const override
		{
			return m_text.getLocalBounds();
		}

		virtual void setScale(sf::Vector2f const& scale)
		{
			m_text.setScale(scale);
		}

		virtual const sf::Vector2f getScale() const
		{
			return m_text.getScale();
		}


		virtual void setOrigin(sf::Vector2f const& origin)
		{
			m_text.setOrigin(origin);
			m_flashText.setOrigin(origin);
		}
		
		virtual const sf::Vector2f getOrigin() const
		{
			return m_text.getOrigin();
		}

		

	private:
		sf::Font m_font;
		sf::Text m_text;
		sf::Text m_flashText;

		sf::Vector2f m_position{0,0};

		void doUpdate(float /*elapsed*/) override
		{
			m_text.setFont(m_font);
			m_text.setPosition(m_position + getShakeOffset() + getOffset() + getCamOffset());
			m_flashText.setPosition(m_position + getShakeOffset() + getOffset() + getCamOffset());
			m_flashText.setScale(m_text.getScale());
		}

		void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const override
		{
			try
			{
				sptr->draw(m_text);
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "error drawing text" << std::endl;
			}
		}

		void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const override
		{
			sptr->draw(m_flashText);
		}

		void doRotate(float rot)
		{
			m_text.setRotation(-rot);
			m_flashText.setRotation(-rot);
		}
	};
}// namespace JamTemplate

#endif
