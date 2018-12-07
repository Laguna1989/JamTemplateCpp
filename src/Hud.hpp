#ifndef GAME_HUD_HPP_INCLUDEGUARD
#define GAME_HUD_HPP_INCLUDEGUARD

#include <string>
#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/Game.hpp"

class Hud : public JamTemplate::GameObject {
public:
	Hud() 
	{
		//m_font.loadFromFile("assets/ARCADECLASSIC.TTF");
	
		//m_text = sf::Text("Score   0", m_font, 24);
	/*	m_text.setPosition(0, 0);
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setOutlineThickness(2);*/
	}

	void increaseScore()
	{
		m_score++;
		//m_text.setString("Score   " + std::to_string(m_score));
	}

private:
	void doUpdate(float const /*elapsed*/) override
	{
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(m_text);
	}

	//sf::Font m_font;
	sf::Text m_text;

	int m_score{ 0 };
};

#endif
