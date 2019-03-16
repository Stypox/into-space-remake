#ifndef _INTO_SPACE_REMAKE_MISC_ACCELERATION_HPP_
#define _INTO_SPACE_REMAKE_MISC_ACCELERATION_HPP_

#include <ostream>

namespace misc {
	class AccelerationSum;

	class Acceleration {
		float m_acceleration;
		float m_rotation;
		bool m_active = true;

	public:
		Acceleration();
		explicit Acceleration(float acceleration);
		Acceleration(float acceleration, float radiansRotation);

		inline float a() const { return m_acceleration * m_active; }
		inline operator float() const { return a(); }
		inline float operator()() const { return a(); }
		float ax() const;
		float ay() const;

		inline float operator* (float deltaTime) const { return deltav(deltaTime); }
		float deltav(float deltaTime) const;
		float deltavx(float deltaTime) const;
		float deltavy(float deltaTime) const;

		inline float rotation() const { return m_rotation; }
		inline bool active() const { return m_active; }	
		
		inline void set(float acceleration) { m_acceleration = acceleration; }
		inline void setRotation(float radiansRotation) { m_rotation = radiansRotation; }
		inline void activate() { m_active = true; }
		inline void deactivate() { m_active = false; }

		AccelerationSum operator+ (const AccelerationSum& accelerationSum) const;
		AccelerationSum operator+ (const Acceleration& acceleration) const;
		AccelerationSum operator- (const AccelerationSum& accelerationSum) const;
		AccelerationSum operator- (const Acceleration& acceleration) const;

		Acceleration& operator+= (float acceleration);
		Acceleration& operator-= (float acceleration);
		Acceleration& operator= (float acceleration);

		inline bool operator== (float acceleration) const { return m_acceleration == acceleration; }
		inline bool operator!= (float acceleration) const { return m_acceleration != acceleration; }

		friend std::ostream& operator<< (std::ostream& stream, const Acceleration& acceleration);
	};

	class AccelerationSum {
		float m_ax, m_ay;

	public:
		explicit AccelerationSum();
		explicit AccelerationSum(float ax, float ay);

		float a() const;
		inline float ax() const { return m_ax; }
		inline float ay() const { return m_ay; }
		inline float deltav(float deltaTime) const { return a() * deltaTime; }
		inline float deltavx(float deltaTime) const { return m_ax * deltaTime; }
		inline float deltavy(float deltaTime) const { return m_ay * deltaTime; }

		AccelerationSum operator+ (const AccelerationSum& accelerationSum) const;
		AccelerationSum operator+ (const Acceleration& acceleration) const;
		AccelerationSum operator- (const AccelerationSum& accelerationSum) const;
		AccelerationSum operator- (const Acceleration& acceleration) const;

		AccelerationSum& operator+= (const AccelerationSum& accelerationSum);
		AccelerationSum& operator+= (const Acceleration& acceleration);
		AccelerationSum& operator-= (const AccelerationSum& accelerationSum);
		AccelerationSum& operator-= (const Acceleration& acceleration);

		friend std::ostream& operator<< (std::ostream& stream, const AccelerationSum& acceleration);
	};
}

#endif