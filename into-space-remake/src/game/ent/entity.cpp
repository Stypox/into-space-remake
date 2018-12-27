#include "entity.h"

#include <math.h>

namespace game::ent {
	bool intersects(const Entity* a, const Entity* b) {
		// assumes a and b are axis-aligned
		return
			a->x() + 0.5f * a->w() > b->x() - 0.5f * b->w() &&
			a->x() - 0.5f * a->w() < b->x() + 0.5f * b->w() &&
			a->y() + 0.5f * a->h() > b->y() - 0.5f * b->h() &&
			a->y() - 0.5f * a->h() < b->y() + 0.5f * b->h();
	}
	float distance(const Entity* a, const Entity* b) {
		// Manhattan distance (Taxicab geometry)
		return std::abs(a->x() - b->x()) + std::abs(a->y() - b->y());
	}
}