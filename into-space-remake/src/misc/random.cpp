#include "./random.h"

namespace misc {
	std::mt19937 Random::generator{std::random_device{}()};
	std::uniform_int_distribution<int> Random::intDistribution{};
	std::uniform_real_distribution<float> Random::realDistribution{};

	int Random::range(int min, int max) {
		intDistribution.param(std::uniform_int_distribution<int>::param_type{min, max});
		return intDistribution(generator);
	}
	float Random::range(float min, float max) {
		realDistribution.param(std::uniform_real_distribution<float>::param_type{min, max});
		return realDistribution(generator);
	}
}