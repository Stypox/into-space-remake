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


	template <typename T = float>
	class Chronometer {
	public:
		using Type = T;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		bool m_stopped;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_pause;

	public:
		Chronometer();

		Type now();
		bool stopped();
		bool paused();

		Type restart();
		Type stop();
		Type pause();
	};


	template <typename T>
	inline Clock<T>::Clock() :
		m_start{std::chrono::high_resolution_clock::now()} {}

	template <typename T>
	inline auto Clock<T>::now() -> Clock<T>::Type {
		return std::chrono::duration<Clock::Type>{std::chrono::high_resolution_clock::now() - m_start}.count();
	}

	template <typename T>
	inline auto Clock<T>::restart() -> Clock<T>::Type {
		Type oldNow = now();
		m_start = std::chrono::high_resolution_clock::now();
		return oldNow;
	}



	template <typename T>
	inline Chronometer<T>::Chronometer() :
		m_start{std::chrono::high_resolution_clock::now()}, m_pause{-1.0f},
		m_stopped{false} {}
	
	template <typename T>
	inline auto Chronometer<T>::now() -> Chronometer<T>::Type {
		if (m_stopped)
			return std::chrono::duration<Clock::Type>{m_start}.count();
		else if (m_pause < 0) // not paused
			return std::chrono::duration<Clock::Type>{std::chrono::high_resolution_clock::now() - m_start}.count();
		else // paused
			return std::chrono::duration<Clock::Type>{m_pause}.count();
	}
	template <typename T>
	bool Chronometer<T>::stopped() {
		return m_stopped;
	}
	template <typename T>
	bool Chronometer<T>::paused() {
		return m_pause >= 0;
	}
	
	template <typename T>
	inline auto Chronometer<T>::restart() -> Chronometer<T>::Type {
		Type oldNow = now();
		m_start = std::chrono::high_resolution_clock::now();
		m_pause = -1.0f;
		return oldNow;
	}
	template <typename T>
	inline auto Chronometer<T>::stop() -> Chronometer<T>::Type {
		if (!m_stopped) {
			m_start = std::chrono::high_resolution_clock::now() - m_start;
			m_stopped = true;
		}
		return std::chrono::duration<Clock::Type>{m_start}.count();
	}
	template <typename T>
	inline auto Chronometer<T>::pause() -> Chronometer<T>::Type {
		if (m_pause < 0) { // not yet paused -> pause
			m_pause = std::chrono::high_resolution_clock::now();
			return m_pause;
		}
		else { // already paused -> set not paused
			m_start += std::chrono::high_resolution_clock::now() - m_pause;
			Type now = m_pause;
			m_pause = -1.0f; // -1 < 0 -> not paused
			return now;
		}
	}
}

#endif