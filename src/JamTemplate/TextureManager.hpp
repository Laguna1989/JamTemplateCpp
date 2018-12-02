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
				m_textures[str] = sf::Texture{};
				m_textures[str].loadFromFile(str);
			}
			return m_textures[str];
		}


	private:
		static std::map<std::string, sf::Texture> m_textures;

	};
}// namespace JamTemplate

#endif
