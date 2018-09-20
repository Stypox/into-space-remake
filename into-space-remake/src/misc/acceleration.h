#ifndef _INTO_SPACE_REMAKE_MISC_ACCELERATION_H_
#define _INTO_SPACE_REMAKE_MISC_ACCELERATION_H_

#include "clock.h"

namespace misc {
	class Acceleration {
		Chronometer m_clock;
		float m_acceleration;
		float m_maxVelocity;
		float m_startVelocity;

		float velocity(float time);

	public:
		Acceleration();
		Acceleration(float acceleration, float maxVelocity, float startVelocity = 0.0f);

		float velocity();

		float restart();
		float stop();
		float pause();
		bool stopped();
		bool paused();

		void setMaxVelocity(float maxVelocity);
		bool reachedMaxVelocity();
		
		float change(float acceleration);
		float change(float acceleration, float maxVelocity);
		float change(float acceleration, float maxVelocity, float startVelocity);
	};
}

#endif