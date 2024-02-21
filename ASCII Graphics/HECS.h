#pragma once
#include <vector>
#include <string>
#include <map>

namespace hecs {
	using Entity = unsigned;

	template <typename T>
	using Vector = std::vector<T>;

	using String = std::string;

	template <typename T, typename U>
	using Map = std::map<T,U>;
}