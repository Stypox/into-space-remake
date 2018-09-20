#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_

#include "../../rend/shared.h"

namespace game::ent {
	class Entity {		
	public:
		virtual GLfloat x() const = 0;
		virtual GLfloat y() const = 0;
		virtual GLfloat sizeX() const = 0;
		virtual GLfloat sizeY() const = 0;
	};
	
	bool intersects(Entity* a, Entity* b);
	// Manhattan distance (Taxicab geometry)
	float distance(Entity* a, Entity* b);
}

#endif