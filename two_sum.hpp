#pragma once

#include <utility>
#include <type_traits>
#include <concepts>
#include <cstddef>

template <auto...>
struct value_sequence;

template <auto FirstValue, auto... OtherValues>
	requires ((std::same_as<decltype(FirstValue), decltype(OtherValues)>) && ...)
struct value_sequence<FirstValue, OtherValues...>
{
};

template <auto, std::size_t, std::size_t, auto...>
struct two_sum_inner;

template <auto Target, std::size_t OuterIndex, std::size_t InnerIndex, auto FirstValue,
		auto... OtherValues>
struct two_sum_inner<Target, OuterIndex, InnerIndex, FirstValue, OtherValues...>
{
	using indices = std::conditional_t<
		Target == FirstValue,
		value_sequence<OuterIndex, InnerIndex>,
		typename two_sum_inner<Target, OuterIndex, InnerIndex + 1, OtherValues...>::indices
	>;
};

template <auto Target, std::size_t OuterIndex, std::size_t InnerIndex>
struct two_sum_inner<Target, OuterIndex, InnerIndex>
{
	using indices = value_sequence<>;
};

template <auto, std::size_t, auto...>
struct two_sum_outer;

template <auto Target, std::size_t OuterIndex, auto FirstValue, auto... OtherValues>
struct two_sum_outer<Target, OuterIndex, FirstValue, OtherValues...>
{
	using inner_result
		= two_sum_inner<Target - FirstValue, OuterIndex, OuterIndex + 1, OtherValues...>::indices;

	using indices = std::conditional_t<
		!std::same_as<inner_result, value_sequence<>>,
		inner_result,
		typename two_sum_outer<Target, OuterIndex + 1, OtherValues...>::indices
	>;
};

template <auto Target, std::size_t OuterIndex>
struct two_sum_outer<Target, OuterIndex>
{
	using indices = value_sequence<>;
};

template <auto Target, auto... Values> 
	requires ((std::same_as<decltype(Target), decltype(Values)>) && ...)
using two_sum = two_sum_outer<Target, 0, Values...>::indices;
