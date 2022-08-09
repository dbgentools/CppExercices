#pragma once
#include <cstdint>

namespace utils {
	/// <summary>
	/// Round a unsigned integer to the upper power of 2
	/// </summary>
	/// <examples>
	/// rtpt_32(5) -> 8
	/// rtpt_32(4) -> 4
	/// </examples>
	/// <param name="x">The number to round</param>
	/// <returns>The nearest up power of 2</returns>
	inline constexpr std::uint32_t rtpt_32(std::uint32_t x) {
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		++x;
		return x;
	}
}