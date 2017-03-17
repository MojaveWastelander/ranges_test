#include <range/v3/detail/config.hpp>
#include <cstddef>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <range/v3/core.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/single.hpp>
#include <range/v3/view/repeat_n.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/unique.hpp>
#include <range/v3/view/generate_n.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/action/join.hpp>
#include <range/v3/action/split.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/mismatch.hpp>

using namespace ranges;

#define func_name std::cout << __func__ << '\n'

void view_all()
{
	func_name;
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	std::cout << (v | view::all);
}

void view_concat()
{
	func_name;
	//                          [1, 6)            [6, 10)            [10, 20)    
	auto rng = view::concat(view::iota(1, 6), view::iota(6, 10), view::iota(10, 20));
	std::cout << rng;
}


// Given a source range and an integer N, produce a range of contiguous ranges where each inner range has N contiguous elements.
// The final range may have fewer than N elements.
void view_chunk()
{
	func_name;
	auto in = view::iota(0, 6);
	auto cnk_2 = in | view::chunk(2);
	auto cnk_3 = in | view::chunk(3);
	std::cout << cnk_2 << '\n' << cnk_3;
}

// Convert the source range to a bounded range, where the type of the end is the same as the begin.
// Useful for iterating over a range with C++'s range-based for loop.
void view_bounded()
{
	func_name;
	// ?
}

#include <range/v3/view/counted.hpp>
// Given an iterator it and a count n, create a range that starts at it and includes the next n elements.
void view_counted()
{
	func_name;
	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7 };
	auto it = v.begin();
	auto rng = view::counted(it, 5);
	std::cout << rng;
}


#include <range/v3/view/delimit.hpp>
// Given a source range and a value, return a new range that ends either at the end of the source or at the
// first occurrence of the value, whichever comes first. Alternatively, view::delimit can be called with an
// iterator and a value, in which case it returns a range that starts at the specified position and ends at
// the first occurrence of the value.
void view_delimit()
{
	func_name;
	auto in = view::iota(0, 20);
	auto rng = in | view::delimit(10); // [0..10)
	auto rng_it = view::delimit(in.begin(), 5); // [0..5)
	std::cout << rng << '\n' << rng_it;
}

#include <range/v3/view/drop.hpp>
// Given a source range and an integral count, return a range consisting of all but the first count elements 
// from the source range, or an empty range if it has fewer elements.
void view_drop()
{
	func_name;
	//          [0..50)       --->   [30..50)
	auto rng = view::iota(0, 50) | view::drop(30);
	std::cout << rng;
}

#include <range/v3/view/drop_exactly.hpp>
// Given a source range and an integral count, return a range consisting of all but the first count elements 
// from the source range. The source range must have at least that many elements.
void view_drop_exactly()
{
	func_name;
	//          [0..50)       --->   [40..50)
	auto rng = view::iota(0, 50) | view::drop_exactly(40);
	std::cout << rng;
}

#include <range/v3/view/drop_while.hpp>
// Remove elements from the front of a range that satisfy a unary predicate (until it's true).
void view_drop_while()
{
	func_name;
	//          [0..50)       --->   [20..50)
	auto rng = view::iota(0, 50) | view::drop_while([](int i)
	{
		return i < 20;
	});
	std::cout << rng;
}

#include <range/v3/view/generate.hpp>
// Given a nullary function, return an infinite range whose elements are generated with the function.
void view_generate()
{
	func_name;
	auto rng = view::generate([]  // [1..inf)
	{
		static int i = 0;
		return ++i;
	}) | view::take(20); // [1..20]
	std::cout << rng;
}

#include <range/v3/view/generate_n.hpp>
// Given a nullary function and a count, return a range that generates the requested number of elements
// by calling the function.
void view_generate_n()
{
	func_name;
	auto rng = view::generate_n([]
	{
		static int i = 0;
		return ++i;
	}, 20); // [1..20]
	std::cout << rng;
}


std::vector<void (*)(void)> funcs = {view_all, view_concat, view_chunk, view_counted, view_delimit, view_drop, view_drop_exactly,
									view_drop_while, view_generate, view_generate_n};

int main()
{
	for (auto fn : funcs)
	{
		fn();
		std::cout << '\n';
	}
}