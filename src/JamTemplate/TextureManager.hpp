#ifndef JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace JamTemplate
{
	class TextureManager
	{
	public:
		TextureManager() = delete;
		

		static sf::Texture& get(std::string const& str)
		{
			if (m_textures.count(str) == 0)
			{
				m_textures[str].loadFromFile(str);

				sf::Image img{ m_textures[str].copyToImage() };
				
				for (unsigned int i = 0; i != img.getSize().x; ++i)
				for (unsigned int j = 0; j != img.getSize().y; ++j)
				{
					if (img.getPixel(i, j).a != 0)
					{
						img.setPixel(i, j, sf::Color(255, 255, 255));
					}
				}

				m_textures[getFlashName(str)].create(m_textures[str].getSize().x, m_textures[str].getSize().y);
				m_textures[getFlashName(str)].update(img);
				//m_textures[getFlashName(str)].u
			}
			return m_textures[str];
		}



		static std::string getFlashName(std::string str)
		{
			return str + "___flash__";
		}
	private:
		static std::map<std::string, sf::Texture> m_textures;

		
	};
}// namespace JamTemplate

#endif
