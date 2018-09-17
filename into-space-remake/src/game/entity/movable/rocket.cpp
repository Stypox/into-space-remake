#include "rocket.h"

#include <iostream>

namespace game::entity::movable {
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

	Rocket::Rocket() :
		Movable{0.0, 0.0} {}

	void Rocket::pickUpIntersecting(std::vector<std::unique_ptr<entity::Item>>& items) {
		for (auto item = items.end(); item != items.begin(); --item) {
			if (intersects(this, item->get())) {
				pickUp(**item);
				items.erase(item, item + 1);
			}
		}
	}
}