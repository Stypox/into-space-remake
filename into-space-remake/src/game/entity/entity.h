#ifndef _INTO_SPACE_REMAKE_GAME_ENTITY_H_
#define _INTO_SPACE_REMAKE_GAME_ENTITY_H_

#include <array>
#include <glm/glm.hpp>

namespace game::entity {
	template<typename V>
	class Entity {		
	public:
		virtual std::array<float, V> vertices() = 0;
	};
}

#endif