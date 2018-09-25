#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_ROCKET_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_MOVABLE_ROCKET_H_

#include <vector>
#include <memory>
#include <math.h>

#include "movable.h"
#include "../item.h"

namespace game::ent::mov {
	class Rocket : public Movable {
		// constants 
		static constexpr float m = 1000.0,				// Rocket mass (kg)
							   Cd = 0.3f,				// Air drag coefficient
							   A = 5.0f,				// Rocket frontal area (m^2)
							   p0 = 101325.0f,			// Sea level air pressure (Pa)
							   T0 = 188.25f,			// Sea level temperature (K)
							   g = 9.80665f,			// Gravitational acceleration (m/s^2)
							   L = 0.0065f,				// Temperature lapse rate (K/m)
							   R = 8.31447f,			// Ideal gas constant (J/(mol * K))
							   M = 0.0289644f,			// Molar mass of dry air (kg/mol)
							   xAcceleration = 1.0f, 	// (m/s^2)
							   yAcceleration = 15.0f;	// (m/s^2)

		// see https://en.wikipedia.org/wiki/Density_of_air
		static constexpr float airTemperature(float h) {
			return T0 - L * h > 0 ? T0 - L * h : 1.0f;
		}
		static constexpr float airPressure(float h) {
			return p0 * pow(1 - (L * h) / (T0), (g * M) / (R * L));
		}
		static constexpr float airDensity(float h) {
			return (airPressure(h) * M) / (R * airTemperature(h));
		}
		// see https://en.wikipedia.org/wiki/Drag_%28physics%29
		static constexpr float airDrag(float v, float h) {
			return 0.5 * airDensity(h) * v * v * Cd * A;
		}

		void pickUp(const Item& item);
		void damage(float velocity);

	public:
		Rocket();

		GLfloat w() const override { return 0.2f; }
		GLfloat h() const override { return 0.4f; }
		GLfloat textureOffset() const override { return 0.0f; }
		GLfloat textureWidth() const override { return 1.0f; }

		void pickUpIntersecting(std::vector<std::unique_ptr<Item>>& items);
	};
}

#endif