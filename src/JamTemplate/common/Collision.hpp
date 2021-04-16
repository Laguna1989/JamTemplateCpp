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

#include "MathHelper.hpp"
#include "Rect.hpp"
#include "Vector.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace jt {
class Collision {
public:
    Collision() = delete;

#if 0
    template <class T>
    static bool Overlaps(T const& Object, jt::Vector2 const& point)
    {
        return (Object->getGlobalBounds().contains(point));
    }

    template <class T>
    class OrientedBoundingBox // Used in the BoundingBoxTest
    {
    public:
        OrientedBoundingBox(T const& Object) // Calculate the four points of the OBB from a
                                             // transformed (scaled, rotated...) sprite
        {
            sf::Transform trans = Object.getTransform();
            auto local = Object.getGlobalBounds();
            Points[0] = trans.transformPoint(0.f, 0.f);
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);*/
        }

        OrientedBoundingBox(std::shared_ptr<T> obj) // Calculate the four points of the OBB from a
                                                    // transformed (scaled, rotated...) sprite
        {
            /*sf::Transform trans = obj->getTransform();
            auto local = obj->getGlobalBounds();
            Points[0] = trans.transformPoint(0.f, 0.f);
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);*/
        }

        jt::Vector2 Points[4];

        void ProjectOntoAxis(const jt::Vector2& Axis, float& Min,
            float& Max) // Project all four points of the OBB onto the given axis and return the
                        // dotproducts of the two outermost points
        {
            Min = (Points[0].x * Axis.x + Points[0].y * Axis.y);
            Max = Min;
            for (int j = 1; j < 4; j++) {
                float Projection = (Points[j].x * Axis.x + Points[j].y * Axis.y);

                if (Projection < Min)
                    Min = Projection;
                if (Projection > Max)
                    Max = Projection;
            }
        }
    };

    template <class U, class V>
    static bool BoundingBoxTest(U const& Object1, V const& Object2)
    {
        OrientedBoundingBox<U> OBB1(Object1);
        OrientedBoundingBox<V> OBB2(Object2);

        // Create the four distinct axes that are perpendicular to the edges of the two rectangles
        jt::Vector2 Axes[4] = { jt::Vector2(OBB1.Points[1].x - OBB1.Points[0].x,
                                    OBB1.Points[1].y - OBB1.Points[0].y),
            jt::Vector2(OBB1.Points[1].x - OBB1.Points[2].x, OBB1.Points[1].y - OBB1.Points[2].y),
            jt::Vector2(OBB2.Points[0].x - OBB2.Points[3].x, OBB2.Points[0].y - OBB2.Points[3].y),
            jt::Vector2(OBB2.Points[0].x - OBB2.Points[1].x, OBB2.Points[0].y - OBB2.Points[1].y) };

        for (int i = 0; i < 4; i++) // For each axis...
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

            // ... project the points of both OBBs onto the axis ...
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

            // ... and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Separating Axis Theorem states that there can be no
            // collision between the rectangles
            if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
                return false;
        }
        return true;
    }

    template <class U, class V>
    static bool BoundingBoxTest(std::shared_ptr<U> obj1, std::shared_ptr<V> obj2)
    {
        OrientedBoundingBox<U> OBB1(obj1);
        OrientedBoundingBox<V> OBB2(obj2);

        // Create the four distinct axes that are perpendicular to the edges of the two rectangles
        jt::Vector2 Axes[4] = { jt::Vector2(OBB1.Points[1].x - OBB1.Points[0].x,
                                    OBB1.Points[1].y - OBB1.Points[0].y),
            jt::Vector2(OBB1.Points[1].x - OBB1.Points[2].x, OBB1.Points[1].y - OBB1.Points[2].y),
            jt::Vector2(OBB2.Points[0].x - OBB2.Points[3].x, OBB2.Points[0].y - OBB2.Points[3].y),
            jt::Vector2(OBB2.Points[0].x - OBB2.Points[1].x, OBB2.Points[0].y - OBB2.Points[1].y) };

        for (int i = 0; i < 4; i++) // For each axis...
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

            // ... project the points of both OBBs onto the axis ...
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

            // ... and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Separating Axis Theorem states that there can be no
            // collision between the rectangles
            if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
                return false;
        }
        return true;
    }

    ////////
    ///// Test for a collision between two sprites by comparing the alpha values of overlapping
    /// pixels
    ///// Supports scaling and rotation
    ///// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel
    /// with
    ///// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
    /////
    ///// This functions creates bitmasks of the textures of the two sprites by
    ///// downloading the textures from the graphics card to memory -> SLOW!
    ///// You can avoid this by using the "CreateTextureAndBitmask" function
    ////////
    // bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, std::uint8_t
    // AlphaLimit = 0);

    ////////
    ///// Replaces Texture::loadFromFile
    ///// Load an imagefile into the given texture and create a bitmask for it
    ///// This is much faster than creating the bitmask for a texture on the first run of
    ///"PixelPerfectTest"
    /////
    ///// The function returns false if the file could not be opened for some reason
    ////////
    // bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);

#endif
    //////
    /// Test for collision using circle collision dection
    /// Radius is averaged from the dimensions of the sprite so
    /// roughly circular objects will be much more accurate
    //////
    template <class U, class V>
    static bool CircleTest(U const& Object1, V const& Object2)
    {
        auto const obj1Size = getSize(Object1);
        auto const obj2Size = getSize(Object2);
        auto const radius1 = (obj1Size.x() + obj1Size.y()) / 4.0f;
        auto const radius2 = (obj2Size.x() + obj2Size.y()) / 4.0f;

        auto const distance = getCenter(Object1) - getCenter(Object2);

        return (
            jt::MathHelper::lengthSquared(distance) <= (radius1 + radius2) * (radius1 + radius2));
    }

    template <class U, class V>
    static bool CircleTest(std::shared_ptr<U> obj1, std::shared_ptr<V> obj2)
    {
        auto const Obj1Size = getSize(obj1);
        auto const Obj2Size = getSize(obj2);
        auto const Radius1 = (Obj1Size.x() + Obj1Size.y()) / 4.0f;
        auto const Radius2 = (Obj2Size.x() + Obj2Size.y()) / 4.0f;

        auto const distance = getCenter(obj1) - getCenter(obj2);

        return (
            jt::MathHelper::lengthSquared(distance) <= (Radius1 + Radius2) * (Radius1 + Radius2));
    }

private:
    template <class U>
    static jt::Vector2 getSize(U const& Object)
    {
        return jt::Vector2(Object.getGlobalBounds().width(), Object.getGlobalBounds().height());
    }

    template <class U>
    static jt::Vector2 getSize(std::shared_ptr<U> obj)
    {
        return jt::Vector2(obj->getGlobalBounds().width(), obj->getGlobalBounds().height());
    }

    template <class U>
    static jt::Vector2 getCenter(U const& obj)
    {
        auto const AABB = obj.getGlobalBounds();
        return jt::Vector2 { AABB.left() + AABB.width() / 2.f, AABB.top() + AABB.height() / 2.f };
    }
    template <class U>
    static jt::Vector2 getCenter(std::shared_ptr<U> obj)
    {
        auto const AABB = obj->getGlobalBounds();
        return jt::Vector2 { AABB.left() + AABB.width() / 2.f, AABB.top() + AABB.height() / 2.f };
    }
};
} // namespace jt

#endif /* COLLISION_H */
