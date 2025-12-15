#pragma once

#include <concepts>
#include <ranges>
#include <string>

namespace Database
{
class CharSpan;
inline constexpr char _splitByte = char(31);

template<typename T>
concept StringIndexable =
	std::ranges::range<T> &&
	requires(T c, size_t i) {
		{ c.size() } -> std::convertible_to<size_t>;
		{ c[i] } -> std::convertible_to<CharSpan>;
};

template<typename T>
concept validfstreamFilePathFormat =
	requires(T path) {
		{ std::fstream(path) };
};

template<typename T>
concept TextLike =
	std::convertible_to<T, CharSpan>;

template<typename T>
concept BinarySerializable =
	std::is_trivially_copyable_v<T>;

template <typename T>
concept TrivialElement =
	std::is_trivially_destructible_v<T> &&
	std::is_trivially_copyable_v<T>;

}