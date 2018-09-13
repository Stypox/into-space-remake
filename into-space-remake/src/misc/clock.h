#ifndef _INTO_SPACE_REMAKE_MISC_CLOCK_H_
#define _INTO_SPACE_REMAKE_MISC_CLOCK_H_

#include <chrono>

namespace misc {
	template <typename T = float>
	class Clock {
	public:
		using Type = T;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

	public:
		Clock();

		Type now();
		Type restart();
	};

	template <typename T>
	inline Clock<T>::Clock() :
		m_start{std::chrono::high_resolution_clock::now()} {}

	template <typename T>
	inline Clock<T>::Type Clock<T>::now() {
		return std::chrono::duration<Clock::Type, std::chrono::seconds>{std::chrono::high_resolution_clock::now() - m_start}.count();
	}
	template <typename T>
	inline Clock<T>::Type Clock<T>::restart() {
		oldNow = now();
		m_start = std::chrono::high_resolution_clock::now();
		return oldNow;
	}
}

#endif