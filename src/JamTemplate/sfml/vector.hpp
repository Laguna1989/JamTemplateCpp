#include <sfml/Graphics.hpp>
namespace JamTemplate
{

// sfml type src/JamTemplate/sfml
class vec final
{	
	sf::Vector2f m_vec;
	float x() {return m_vec.x;};
	float y() {return m_vec.y;};
};

// common_vec.hpp
vec operator- (vec const& a, vec const& b)
{
	...
}

}