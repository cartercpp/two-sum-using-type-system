# two-sum-using-type-system

The classic LeetCode "Two Sum" problem solved entirely in the C++ type system. No runtime work, no `std::vector`, no `if constexpr` — just template recursion, partial specialization, and `std::conditional_t`.

## API

```cpp
#include "two_sum.hpp"

using result = two_sum<9, 2, 7, 11, 15>;
//                     ^  ^^^^^^^^^^^^
//                target    values

static_assert(std::same_as<result, value_sequence<0, 1>>);
// indices 0 and 1 — i.e. 2 + 7 = 9
```

The target and every value share a single type, enforced by a `requires` clause on the alias. The result is a `value_sequence<i, j>` where `Values[i] + Values[j] == Target`, or `value_sequence<>` if no such pair exists.

## How it works

The implementation is the brute-force O(n²) two-sum, but each "loop iteration" is a template instantiation rather than a runtime step.

- **`two_sum_outer`** picks the outer index, then hands the rest of the pack to the inner search with the target reduced by the outer value.
- **`two_sum_inner`** walks the remaining pack looking for the reduced target. On a match it produces `value_sequence<OuterIndex, InnerIndex>`. On exhaustion it produces `value_sequence<>`.
- **`std::conditional_t`** branches at the type level: if the inner search returned a non-empty sequence, the outer template returns it; otherwise it recurses with the next outer index.
- **Empty-pack partial specializations** terminate both recursions.

The compiler computes the answer during instantiation and exposes it as a type. There is no runtime.

## Build

```bash
g++ -std=c++20 -O2 main.cpp -o two_sum
./two_sum
```

Requires C++20: `auto` non-type template parameters, `std::same_as`, alias-template `requires` clauses.

## Demo

A short walkthrough is on Instagram: [reel link from repo description].
