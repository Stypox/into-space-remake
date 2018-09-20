#include "entity.h"

namespace game::ent {
	bool intersects(Entity* a, Entity* b) {
		// assumes a and b are axis-aligned
		return
			a->x() + 0.5f * a->sizeX() > b->x() - 0.5f * b->sizeX() &&
			a->x() - 0.5f * a->sizeX() < b->x() + 0.5f * b->sizeX() &&
			a->y() + 0.5f * a->sizeY() > b->y() - 0.5f * b->sizeY() &&
			a->y() - 0.5f * a->sizeY() < b->y() + 0.5f * b->sizeY();

	}
	float distance(Entity* a, Entity* b) {
		// Manhattan distance (Taxicab geometry)
		return a->x() - b->x() + a->y() - b->y();
	}
}