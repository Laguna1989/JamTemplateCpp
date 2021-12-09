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

#include "math_helper.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <memory>

namespace jt {
class Collision {
public:
    Collision() = delete;

    /// Test for collision using circle collision detection
    ///
    /// Radius is averaged from the dimensions of the sprite so roughly circular objects will be
    /// much more accurate
    ///
    /// The objects need to offer the GetGlobalBounds() function
    ///
    /// \tparam U Type of obj1
    /// \tparam V Type of obj2
    /// \param obj1 Object 1
    /// \param obj2 Object 2
    /// \return
    template <class U, class V>
    static bool CircleTest(U const& obj1, V const& obj2)
    {
        auto const obj1Size = getSize(obj1);
        auto const obj2Size = getSize(obj2);
        auto const radius1 = (obj1Size.x + obj1Size.y) / 4.0f;
        auto const radius2 = (obj2Size.x + obj2Size.y) / 4.0f;

        auto const distance = getCenter(obj1) - getCenter(obj2);

        return (
            jt::MathHelper::lengthSquared(distance) <= (radius1 + radius2) * (radius1 + radius2));
    }

    template <class U, class V>
    static bool CircleTest(std::shared_ptr<U> obj1, std::shared_ptr<V> obj2)
    {
        auto const Obj1Size = getSize(obj1);
        auto const Obj2Size = getSize(obj2);
        auto const Radius1 = (Obj1Size.x + Obj1Size.y) / 4.0f;
        auto const Radius2 = (Obj2Size.x + Obj2Size.y) / 4.0f;

        auto const distance = getCenter(obj1) - getCenter(obj2);

        return (
            jt::MathHelper::lengthSquared(distance) < ((Radius1 + Radius2) * (Radius1 + Radius2)));
    }

private:
    template <class U>
    static jt::Vector2f getSize(U const& Object)
    {
        return jt::Vector2f { Object.getGlobalBounds().width, Object.getGlobalBounds().height };
    }

    template <class U>
    static jt::Vector2f getSize(std::shared_ptr<U> obj)
    {
        return jt::Vector2f { obj->getGlobalBounds().width, obj->getGlobalBounds().height };
    }

    template <class U>
    static jt::Vector2f getCenter(U const& obj)
    {
        auto const AABB = obj.getGlobalBounds();
        return jt::Vector2f { AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f };
    }
    template <class U>
    static jt::Vector2f getCenter(std::shared_ptr<U> obj)
    {
        auto const AABB = obj->getGlobalBounds();
        return jt::Vector2f { AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f };
    }
};
} // namespace jt

#endif /* COLLISION_H */
