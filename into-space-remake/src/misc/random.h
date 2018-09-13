#ifndef _INTO_SPACE_REMAKE_MISC_RANDOM_H_
#define _INTO_SPACE_REMAKE_MISC_RANDOM_H_

#include <random>

namespace misc {
	class Random {
		static std::mt19937 generator;
		static std::uniform_int_distribution<int> intDistribution;
		static std::uniform_real_distribution<float> realDistribution;

	public:
		inline static int range(int max) { return range(0, max); }
		static int range(int min, int max);
		inline static float range(float max) { return range(0.0f, max); }
		static float range(float min, float max);

		static bool boolean();
	};
}

#endif