/*
 * File:   collision.h
 * Authors: Nick Koirala (original version), ahnonay (SFML2 compatibility)
 *
 * Collision Detection and handling class
 * For SFML2.

Notice from the original version:

(c) 2009 - LittleMonkey Ltd

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but
   is not required.

2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
   source distribution.

 *
 * Created on 30 January 2009, 11:02
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace JamTemplate {
	class Collision
	{
	public:
		Collision() = delete;
		////////
		///// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
		///// Supports scaling and rotation
		///// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
		///// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
		///// 
		///// This functions creates bitmasks of the textures of the two sprites by
		///// downloading the textures from the graphics card to memory -> SLOW!
		///// You can avoid this by using the "CreateTextureAndBitmask" function
		////////
		//bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);

		////////
		///// Replaces Texture::loadFromFile
		///// Load an imagefile into the given texture and create a bitmask for it
		///// This is much faster than creating the bitmask for a texture on the first run of "PixelPerfectTest"
		///// 
		///// The function returns false if the file could not be opened for some reason
		////////
		//bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);

		//////
		/// Test for collision using circle collision dection
		/// Radius is averaged from the dimensions of the sprite so
		/// roughly circular objects will be much more accurate
		//////
		template <typename U, typename V>
		static bool CircleTest( U const& Object1, V const& Object2)
		{
			sf::Vector2f Obj1Size = GetSpriteSize(Object1);
			sf::Vector2f Obj2Size = GetSpriteSize(Object2);
			float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
			float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

			sf::Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);

			return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
		}

		////////
		///// Test for bounding box collision using the Separating Axis Theorem
		///// Supports scaling and rotation
		////////
		//bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

	private:

		template<typename U>
		static sf::Vector2f GetSpriteSize(U const& Object)
		{
			//sf::IntRect OriginalSize = Object.getTextureRect();
			//sf::Vector2f Scale = Object.getScale();
			//return sf::Vector2f(OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
			return sf::Vector2f(Object.getGlobalBounds().width, Object.getGlobalBounds().height);
		}
		template <typename U>
		static sf::Vector2f GetSpriteCenter(U const& Object)
		{
			sf::FloatRect AABB = Object.getGlobalBounds();
			return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
		}
		//// TODO is there any way to reduce this redundancy?
		//static sf::Vector2f GetSpriteCenter(V const& Object)
		//{
		//	sf::FloatRect AABB = Object.getGlobalBounds();
		//	return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
		//}
	};
}

#endif	/* COLLISION_H */
