#ifndef JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD
#define JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD

#include <random>
#include <SFML/Graphics.hpp>

namespace JamTemplate {

	class Random
	{
	public:
		/// this class shall never be instantiated, but only used as a pure-static class 
		Random() = delete;
		
		static int getInt(int min = 0, int max = 100);
		static float getFloat(float min = 0.0, float max = 1.0);
		static float getFloatGauss(float mu = 0, float sigma = 1);
		// c has to be between 0 and 1
		static bool getChance(float c = 0.5f);

		static sf::Color const getRandomColor();

	private:
		static std::default_random_engine m_engine;
		
	};
}
#endif
