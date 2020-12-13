#pragma once
#include <array>
#include <functional>
#include <optional>
#include <tuple>

namespace stackmachine
{
using std::array;
using std::optional;
using std::tuple;

/** Possible assembly operations in the spec */
enum class Opcode
{
  unreachable = 0,
  Push,
  Pop,
  Store,
  Load,
};

/** Single entry at an address in the virtual memory */
using MemorySegment = char;

/** Segment of virtual memory */
template <std::size_t Sz> using Memory = array<MemorySegment, Sz>;

using Code =
    std::tuple<Opcode, optional<MemorySegment>, optional<MemorySegment>>;

/** 
 * @brief Interface for host functions to access stack memory
 */
struct StackHandle
{
  virtual MemorySegment pop() = 0;
  virtual MemorySegment peek() const = 0;
  virtual void push(MemorySegment) = 0;
};

using HostFunction = std::function<void(StackHandle&)>;

} // namespace stackmachine
