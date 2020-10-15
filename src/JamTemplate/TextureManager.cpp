#include "TextureManager.hpp"
#include <map>

namespace JamTemplate {
std::map<std::string, sf::Texture> TextureManager::m_textures;
std::vector<std::vector<std::pair<sf::Color, sf::Color>>> TextureManager::m_selectiveColorReplace {};
}
