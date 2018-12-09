#ifndef JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD
#define JAMTEMPLATE_MATHHELPER_HPP_INCLUDEGUARD

#include <vector>

namespace JamTemplate {

	class MathHelper {
	public:
		MathHelper() = delete;

		template<typename T>
		static std::vector<T> vectorBetween(T const& a, T const& b)
		{
			std::vector<T> values;
			for (T i = a; i != b; ++i)
			{
				values.push_back(i);
			}
			return values;
		}
	};

} // namespace JamTemplate

#endif
