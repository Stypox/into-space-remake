#include "acceleration.h"

#include <math.h>

namespace misc {
	Acceleration::Acceleration() :
		Acceleration{0.0f, 0.0f} {}
	Acceleration::Acceleration(float acceleration) :
		Acceleration{acceleration, 0.0f} {}
	Acceleration::Acceleration(float acceleration, float radiansRotation) :
		m_acceleration{acceleration}, m_rotation{radiansRotation} {}

	float Acceleration::ax() const {
		return a() * std::cos(m_rotation);
	}
	float Acceleration::ay() const {
		return a() * std::sin(m_rotation);
	}
	float Acceleration::deltav(float deltaTime) const {
		return a() * deltaTime;
	}
	float Acceleration::deltavx(float deltaTime) const {
		return ax() * deltaTime;
	}
	float Acceleration::deltavy(float deltaTime) const {
		return ay() * deltaTime;
	}

	void Acceleration::toggleActive() {
		m_active = !m_active;
	}

	AccelerationSum Acceleration::operator+ (const AccelerationSum& accelerationSum) const {
		return AccelerationSum{ax() + accelerationSum.ax(), ay() + accelerationSum.ay()};
	}
	AccelerationSum Acceleration::operator+ (const Acceleration& acceleration) const {
		return AccelerationSum{ax() + acceleration.ax(), ay() + acceleration.ay()};
	}
	AccelerationSum Acceleration::operator- (const AccelerationSum& accelerationSum) const {
		return AccelerationSum{ax() - accelerationSum.ax(), ay() - accelerationSum.ay()};
	}
	AccelerationSum Acceleration::operator- (const Acceleration& acceleration) const {
		return AccelerationSum{ax() - acceleration.ax(), ay() - acceleration.ay()};
	}

	Acceleration& Acceleration::operator+= (float acceleration) {
		m_acceleration += acceleration;
		return *this;
	}
	Acceleration& Acceleration::operator-= (float acceleration) {
		m_acceleration -= acceleration;
		return *this;
	}
	Acceleration& Acceleration::operator= (float acceleration) {
		m_acceleration = acceleration;
		return *this;
	}

	std::ostream& operator<< (std::ostream& stream, const Acceleration& acceleration) {
		stream << acceleration.m_acceleration << '*' << acceleration.m_active;
		return stream;
	}



	AccelerationSum::AccelerationSum() :
		AccelerationSum{0.0f, 0.0f} {}
	AccelerationSum::AccelerationSum(float ax, float ay) :
		m_ax{ax}, m_ay{ay} {}

	float AccelerationSum::a() const {
		return std::sqrt(m_ax * m_ax + m_ay * m_ay);
	}

	AccelerationSum AccelerationSum::operator+ (const AccelerationSum& accelerationSum) const {
		return AccelerationSum{m_ax + accelerationSum.ax(), m_ay + accelerationSum.ay()};
	}
	AccelerationSum AccelerationSum::operator+ (const Acceleration& acceleration) const {
		return AccelerationSum{m_ax + acceleration.ax(), m_ay + acceleration.ay()};
	}
	AccelerationSum AccelerationSum::operator- (const AccelerationSum& accelerationSum) const {
		return AccelerationSum{m_ax - accelerationSum.ax(), m_ay - accelerationSum.ay()};
	}
	AccelerationSum AccelerationSum::operator- (const Acceleration& acceleration) const {
		return AccelerationSum{m_ax - acceleration.ax(), m_ay - acceleration.ay()};
	}

	AccelerationSum& AccelerationSum::operator+= (const AccelerationSum& accelerationSum) {
		m_ax += accelerationSum.m_ax;
		m_ay += accelerationSum.m_ay;
		return *this;
	}
	AccelerationSum& AccelerationSum::operator+= (const Acceleration& acceleration) {
		m_ax += acceleration.ax();
		m_ay += acceleration.ay();
		return *this;
	}
	AccelerationSum& AccelerationSum::operator-= (const AccelerationSum& accelerationSum) {
		m_ax -= accelerationSum.m_ax;
		m_ay -= accelerationSum.m_ay;
		return *this;
	}
	AccelerationSum& AccelerationSum::operator-= (const Acceleration& acceleration) {
		m_ax -= acceleration.ax();
		m_ay -= acceleration.ay();
		return *this;
	}
}