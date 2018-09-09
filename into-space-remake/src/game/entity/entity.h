#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_

#include <array>
#include <glm/glm.hpp>

#include "../../render/shared.h"

namespace game::entity {
	class Entity {		
	public:
		virtual GLfloat x() const = 0;
		virtual GLfloat y() const = 0;
	};
}

#endif