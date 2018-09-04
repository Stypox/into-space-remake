#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_ENTITY_H_

#include <array>
#include <glm/glm.hpp>

#include "../../render/shared.h"

namespace game::entity {
	template<size_t V>
	class Entity {		
	public:
		virtual std::array<float, render::vertexSize * V> vertices() = 0;
	};
}

#endif