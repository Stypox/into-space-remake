#include "rocket.h"

#include <iostream>
#include <math.h>

#include "../../../app/event/key.h"

namespace game::ent::mov {
	using namespace app::event;

	void Rocket::pickUp(const Item& item) {
		switch (item.type()) {
		case Item::fuel0:
			std::cout << "fuel 0\n";
			break;
		case Item::fuel1:
			std::cout << "fuel 1\n";
			break;
		case Item::fuel2:
			std::cout << "fuel 2\n";
			break;
		case Item::money0:
			std::cout << "money 0\n";
			break;
		case Item::money1:
			std::cout << "money 1\n";
			break;
		case Item::money2:
			std::cout << "money 2\n";
			break;
		case Item::repair:
			std::cout << "repair\n";
			break;
		}
	}
	void Rocket::updateRotation(float deltaTime) {
		if (m_gravity.active()) {
			m_rotation += m_rotationVelocity * deltaTime;
		}
		else {
			//normalize rotation
			m_rotation -= std::floor(m_rotation / (2.0f * M_PI)) * 2.0f * M_PI;

			// the inclination at which the Rocket laying direction changes
			// (when the Rocket is / it falls right; \ -> left)
			constexpr float barycenterOnYAxis = 0.463647609f; // = std::atan(width / height)
			// the rocket should fall anticlockwise
			if	   ((m_rotation > 0.0f								&& m_rotation <					barycenterOnYAxis	) ||
					(m_rotation > 0.5f * M_PI						&& m_rotation < M_PI		  - barycenterOnYAxis	) ||
					(m_rotation > M_PI								&& m_rotation < M_PI		  + barycenterOnYAxis	) ||
					(m_rotation > 1.5f * M_PI						&& m_rotation < 2.0f * M_PI	  - barycenterOnYAxis	)) {
				m_rotation -= 5.0f * M_PI * deltaTime;
			}
			// the rocket should fall clockwise
			else if((m_rotation > 				barycenterOnYAxis	&& m_rotation < 0.5f * M_PI							) ||
					(m_rotation > M_PI		  - barycenterOnYAxis	&& m_rotation < M_PI								) ||
					(m_rotation > M_PI		  + barycenterOnYAxis	&& m_rotation < 1.5f * M_PI							) ||
					(m_rotation > 2.0f * M_PI -	barycenterOnYAxis	&& m_rotation < 2.0f * M_PI							)) {
				m_rotation += 10.0f * M_PI * deltaTime;
			}

			// round rotation if near axes
			constexpr float roundingValue = 0.05f; // (rad)
			if ((m_rotation > 2.0f * M_PI - roundingValue && m_rotation < 0.0f) || (m_rotation > 0.0f && m_rotation < roundingValue))
				m_rotation = 0.0f;
			else if (m_rotation > 0.5f * M_PI - roundingValue && m_rotation < 0.5f * M_PI + roundingValue)
				m_rotation = 0.5f * M_PI;
			else if (m_rotation > 1.0f * M_PI - roundingValue && m_rotation < 1.0f * M_PI + roundingValue)
				m_rotation = 1.0f * M_PI;
			else if (m_rotation > 1.5f * M_PI - roundingValue && m_rotation < 1.5f * M_PI + roundingValue)
				m_rotation = 1.5f * M_PI;
		}

		m_engine.setRotation(m_rotation + 0.5f * M_PI); // the rocket rotation is 0 when it is vertical, not horizontal (along x axis), so summing 90°
		m_drag.setRotation((m_vy == 0.0f && m_vx == 0.0f) ? 0.0f : std::atan(m_vy / m_vx));
	}
	void Rocket::damage(float velocity) {
		m_integrity -= std::abs(velocity) * 0.1f;
	}

	Rocket::Rocket() :
		Movable{0.0f, 0.0f}, m_vx{0.0f},
		m_vy{0.0f}, m_engine{/*TODO*/12.0f, 0.5f * M_PI},
		m_drag{}, m_gravity{g, 1.5 * M_PI},
		m_rotation{0.0f}, m_rotationVelocity{0.0f},
		m_integrity{/*TODO*/0.0f} {
		m_engine.deactivate();
	}

	bool Rocket::process(std::shared_ptr<Event> event) {
		if (event->type == Event::key) {
			Key* keyEvent = dynamic_cast<Key*>(event.get());
			switch (keyEvent->key) {
			case GLFW_KEY_W: case GLFW_KEY_UP:
				switch (keyEvent->type) {
				case Key::press:
					m_engine.activate();
					return true;
				case Key::release:
					m_engine.deactivate();
					return true;
				default:
					return false;
				}
			case GLFW_KEY_A: case GLFW_KEY_LEFT:
				switch (keyEvent->type) {
				case Key::press:
					m_rotationVelocity += defaultRotationVelocity;
					return true;
				case Key::release:
					m_rotationVelocity -= defaultRotationVelocity;
					return true;
				default:
					return false;
				}
			case GLFW_KEY_S: case GLFW_KEY_DOWN:
				switch (keyEvent->type) {
				case Key::press:
					m_engine.deactivate();
					return true;
				default:
					return false;
				}
			case GLFW_KEY_D: case GLFW_KEY_RIGHT:
				switch (keyEvent->type) {
				case Key::press:
					m_rotationVelocity -= defaultRotationVelocity;
					return true;
				case Key::release:
					m_rotationVelocity += defaultRotationVelocity;
					return true;
				default:
					return false;
				}
			default:
				return false;
			}
		}
		else return false;
	}
	void Rocket::updatePosition(float deltaTime) {
		updateRotation(deltaTime);

		// calculate acceleration sum
		auto accelSum = m_engine + m_drag + m_gravity;

		// update velocity
		m_vx += accelSum.deltavx(deltaTime);
		m_vy += accelSum.deltavy(deltaTime);

		// update position and check if rocket is below ground
		m_y += m_vy * deltaTime;
		if (m_y >= 0.2f) {
			m_x += m_vx * deltaTime;
			m_gravity.activate();
		}
		else {
			m_y = 0.2f;
			if (m_vy < 0)
				damage(m_vy);

			m_vy = 0.0f;
			m_vx = 0.0f;
			m_gravity.deactivate();
		}

		// update air friction
		float v = sqrt(m_vx * m_vx + m_vy * m_vy);
		m_drag = airDrag(v, m_y) / m;

		std::cout << "\r                vx: " << m_vx << "  vy: " << m_vy << "   a: " << accelSum << "   v: " << v << " drag: " << m_drag;
	}

	void Rocket::pickUpIntersecting(std::vector<std::unique_ptr<ent::Item>>& items) {
		for (auto item = items.rbegin(); item != items.rend(); ++item) {
			if (intersects(this, item->get())) {
				pickUp(**item);
				items.erase(std::next(item).base());
			}
		}
	}
}