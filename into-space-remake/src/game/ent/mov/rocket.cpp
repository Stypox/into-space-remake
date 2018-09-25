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
	void Rocket::damage(float velocity) {
		m_integrity -= std::abs(velocity) * 0.1f;
	}

	Rocket::Rocket() :
		Movable{0.0f, 0.0f}, m_onGround{true} {}

	bool Rocket::process(std::shared_ptr<Event> event) {
		if (event->type == Event::key) {
			Key* keyEvent = dynamic_cast<Key*>(event.get());
			switch (keyEvent->key) {
			case GLFW_KEY_W: case GLFW_KEY_UP:
				switch (keyEvent->type) {
				case Key::press:
					m_yAccel += yAcceleration;
					return true;
				case Key::release:
					m_yAccel -= yAcceleration;
					return true;
				default:
					return false;
				}
			case GLFW_KEY_A: case GLFW_KEY_LEFT:
				switch (keyEvent->type) {
				case Key::press:
					m_xAccel -= xAcceleration;
					return true;
				case Key::release:
					m_xAccel += xAcceleration;
					return true;
				default:
					return false;
				}
			case GLFW_KEY_S: case GLFW_KEY_DOWN:
				switch (keyEvent->type) {
				case Key::press:
					// TODO turn off engine
					return true;
				default:
					return false;
				}
			case GLFW_KEY_D: case GLFW_KEY_RIGHT:
				switch (keyEvent->type) {
				case Key::press:
					m_xAccel += xAcceleration;
					return true;
				case Key::release:
					m_xAccel -= xAcceleration;
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
		// calculate velocity along x and y
		float vX = m_xAccel.velocity();
		float vY = m_yAccel.velocity();

		// update position
		m_x += vX * deltaTime;
		m_y += vY * deltaTime;

		std::cout << "  vY: " << vY << "  vX: " << vX << "  aY: " << m_yAccel;
		if (m_y < 0.0f) {
			m_onGround = true;
			m_y = 0.0f;
			damage(vY);
			vY = 0.0f;
			m_yAccel.reset();
		}
		else if (m_onGround) {
			m_onGround = false;
			//m_accelerations[negY] = g;
		}

		// update air friction
		float v = sqrt(vX * vX + vY * vY);
		std::cout << " Velocity: " << v;
		if (round(v * 10000.0f) / 10000.0f != 0) {
			float dragAccel = airDrag(v, m_y) / m;

			m_xAccel -= (dragAccel * vX) / (v);
			m_yAccel -= (dragAccel * vY) / (v);
			std::cout << " Drag: " << dragAccel;
		}
		std::cout << "                          ";
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