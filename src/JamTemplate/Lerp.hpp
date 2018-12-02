#ifndef JAMTEMPLATE_LERP_HPP_INCLUDEGUARD
#define JAMTEMPLATE_LERP_HPP_INCLUDEGUARD

#include <assert.h>

namespace JamTemplate
{
	class Lerp {
	public:
		Lerp() = delete;

		template <typename T>
		static T linear(T const& a, T const& b, T const& t)
		{
			assert(t >= 0 && t <= 1);
			return (1 - t) * a + t * b;
		}

		template <typename T>
		static T cosine(T const& a, T const& b, T const& t)
		{
			assert(t >= 0 && t <= 1);
			float tRemapCosine = (1.0 - cos(t * 3.1415926f)) * 0.5f;
			return linear(a, b, tRemapCosine);
		}
	};
}


#endif
