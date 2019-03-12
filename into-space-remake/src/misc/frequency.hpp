#ifndef _INTO_SPACE_REMAKE_MISC_FREQUENCY_HPP_
#define _INTO_SPACE_REMAKE_MISC_FREQUENCY_HPP_

#include <vector>

#include "clock.hpp"

namespace misc {
	class FrequencyNr {
		static Clock<> m_clock;

		std::vector<float> m_pings;
		unsigned int m_currentPing;

	public:
		FrequencyNr(const int nrPings);

		void ping();

		float frequency();
		float seconds();
	};


	class FrequencyTime {
		static Clock<> m_clock;

		std::vector<float> m_pings;
		float m_timeMax;

		void removeOldPings();

	public:
		FrequencyTime(const float timeMax);

		void ping();

		float frequency();
		float seconds();
	};
}

#endif