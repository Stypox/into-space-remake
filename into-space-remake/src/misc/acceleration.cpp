#include "acceleration.h"

#include <algorithm>

namespace misc {
	float Acceleration::velocity(float time) {
		if (m_acceleration >= 0)
			return std::min(m_acceleration * time + m_startVelocity, m_maxVelocity);
		else
			return std::max(m_acceleration * time + m_startVelocity, m_maxVelocity);
	}

	Acceleration::Acceleration() :
		Acceleration{0.0f, 0.0f} {}
	Acceleration::Acceleration(float acceleration, float maxVelocity, float startVelocity) :
		m_clock{}, m_acceleration{acceleration},
		m_maxVelocity{maxVelocity}, m_startVelocity{startVelocity} {}

	float Acceleration::velocity() {
		return velocity(m_clock.now());
	}

	float Acceleration::restart() {
		return velocity(m_clock.restart());
	}
	float Acceleration::stop() {
		return velocity(m_clock.stop());
	}
	float Acceleration::pause() {
		return velocity(m_clock.pause());
	}
	bool Acceleration::stopped() {
		return m_clock.stopped();
	}
	bool Acceleration::paused() {
		return m_clock.paused();
	}

	void Acceleration::setMaxVelocity(float maxVelocity) {
		m_maxVelocity = maxVelocity;
	}
	bool Acceleration::reachedMaxVelocity() {
		return m_maxVelocity == velocity();
	}

	float Acceleration::change(float acceleration) {
		m_acceleration = acceleration;
		m_startVelocity = velocity();

		m_clock.restart();
		return m_startVelocity;
	}
	float Acceleration::change(float acceleration, float maxVelocity) {
		m_acceleration = acceleration;
		m_maxVelocity = maxVelocity;
		m_startVelocity = velocity();

		m_clock.restart();
		return m_startVelocity;
	}
	float Acceleration::change(float acceleration, float maxVelocity, float startVelocity) {
		float velocityOld = velocity();

		m_acceleration = acceleration;
		m_maxVelocity = maxVelocity;
		m_startVelocity = startVelocity;
		
		m_clock.restart();
		return velocityOld;
	}
}