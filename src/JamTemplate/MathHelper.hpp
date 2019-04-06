#ifndef JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include <vector>

namespace JamTemplate {

	class MathHelper {
	public:
		MathHelper() = delete;

		// create a vector with numbers between a and b (both inclusive)
		// when called with vectorBetween(4,9) the resulting vector will be
		// [4, 5, 6, 7, 8, 9]
		template<typename T>
		static std::vector<T> vectorBetween(T const& a, T const& b)
		{
			std::vector<T> values;
			for (T i = a; i != b+1; ++i)
			{
				values.push_back(i);
			}
			return values;
		}

		static float lengthSquared(sf::Vector2f v)
		{
			return v.x*v.x + v.y*v.y;
		}

		static float length(sf::Vector2f v)
		{
			return std::sqrt(v.x*v.x + v.y*v.y);
		}

		static float rad2deg(float a)
		{
			return a * 180.0f / 3.1415926f;
		}
		static float deg2rad (float a)
		{
			return a / 180.0f * 3.1415926f;
		}
	};

} // namespace JamTemplate

#endif
