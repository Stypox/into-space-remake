#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ITEM_H_

#include "entity.h"

namespace game::entity {
	constexpr size_t nrVerticesItem = 4;

	class Item : public Entity<nrVerticesItem> {
		// the enum values represent the position in the texture file 
		enum Type : char {
			fuel0  = 0,
			fuel1  = 1,
			fuel2  = 2,
			money0 = 3,
			money1 = 4,
			money2 = 5,
			repair = 6,
		};

		const Type m_type;
		const float m_x, m_y;

	public:
		Item(Type type, float x, float y);

		std::array<float, nrVerticesItem * render::vertexSize> vertices() const override;
	};
}

#endif