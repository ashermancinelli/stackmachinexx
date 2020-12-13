#pragma once
#include <array>
#include <stackmachine/Types.hpp>
#include <string>
#include <vector>

namespace stackmachine::stl
{
using std::array;
using std::vector;

template<std::size_t StackSize, std::size_t HeapSize>
constexpr vector<::stackmachine::types::function_t<StackSize, HeapSize>> stl;
}  // namespace stackmachine::stl
