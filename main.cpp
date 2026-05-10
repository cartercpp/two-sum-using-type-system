#include <concepts>
#include <cstddef>
#include "two_sum.hpp"

int main()
{
	using indices = two_sum<5, 0, 1, 2, 3, 4>;
	static_assert(std::same_as<indices, value_sequence<std::size_t{1}, std::size_t{4}>> , "x");
}
