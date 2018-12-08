#ifndef JAMTEMPLATE_LERP_HPP_INCLUDEGUARD
#define JAMTEMPLATE_LERP_HPP_INCLUDEGUARD

#include <assert.h>

namespace JamTemplate
{
	class Lerp {
	public:
		Lerp() = delete;

		// linear interpolation between a and b with t between 0 and 1
		template <typename T>
		static T linear(T const& a, T const& b, T const& ti)
		{
			auto t = precheck(ti);
			assert(t >= 0.0 && t <= 1.0);
			return (1.0f - t) * a + t * b;
		}

		template <typename T>
		static T cosine(T const& a, T const& b, T const& t)
		{
			assert(t >= 0 && t <= 1);
			float tRemapCosine = (1.0f - static_cast<float>(cos(t * 3.1415926f))) * 0.5f;
			return linear(a, b, tRemapCosine);
		}

	private:
		template <typename T>
		static T precheck(T const& ti)
		{
			T t = ti;
			if (t < 0) t = 0;
			if (t > 1) t = 1;
			return t;
		}
	};
}


#endif
