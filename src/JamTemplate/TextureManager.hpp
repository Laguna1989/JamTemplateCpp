#ifndef JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_TEXTUREMANAGER_HPP_INCLUDEGUARD

#include <map>
#include <assert.h>
#include <vector>
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
		// This will chance all textures in m_textures and might thus not be revertible
		// Warning: due to slow copy process from graphics memory to ram and back to graphics this should not be called frequently!
		// Only works for textures obtained from this (not for colors of shapes or whatever)
		// \param in and out are used for lookups
		// if a color is used which is not contained in in, the color will be unchanged
		static void swapPalette(std::vector<sf::Color> in, std::vector<sf::Color> out)
		{
			assert(in.size() == out.size());
			for (auto& kvp : m_textures)
			{

				sf::Image img = kvp.second.copyToImage();
				
				for (unsigned i = 0; i != img.getSize().x; ++i)
				for (unsigned j = 0; j != img.getSize().x; ++j)
				{
					auto col = img.getPixel(i, j);
					// for this pixel check for each color in lookup
					for (size_t idx = 0; idx != in.size(); ++idx)
					{
						if (in[idx] == col)
						{
							img.setPixel(i, j, out[idx]);
							break;
						}
					}
				}
				kvp.second.loadFromImage(img);
			}
		}

	private:
		static std::map<std::string, sf::Texture> m_textures;

	};
}// namespace JamTemplate

#endif
