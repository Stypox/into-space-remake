#ifndef _INTO_SPACE_REMAKE_GAME_ENT_ENTITY_H_
#define _INTO_SPACE_REMAKE_GAME_ENT_ENTITY_H_

#include <glad/glad.h>

namespace game::ent {
	class Entity {		
	public:
		virtual GLfloat x() const = 0;
		virtual GLfloat y() const = 0;
		virtual GLfloat w() const = 0;
		virtual GLfloat h() const = 0;
		virtual GLfloat rotation() const = 0;
	};
	
	bool intersects(const Entity* a, const Entity* b);
	// Manhattan distance (Taxicab geometry)
	float distance(const Entity* a, const Entity* b);
}

#endif