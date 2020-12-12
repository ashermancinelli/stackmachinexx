#pragma once
#include <array>
#include <functional>
#include <optional>
#include <tuple>

namespace stackmachine::detail
{
using std::array;
using std::optional;
using std::tuple;

/** Possible assembly operations in the spec */
enum class Opcode
{
  Noop = 0,
  Push,
  Pop,
  Store,
  Load,
};

/** Single entry at an address in the virtual memory */
using MemorySegment = char;

/** Segment of virtual memory */
template <std::size_t Sz> using Memory = array<MemorySegment, Sz>;

/** Handle given to host functions and intrinsics */
template <std::size_t Sz> struct StackHandle
{
  StackHandle(Memory<Sz> &s, std::size_t &it) : _stack{s}, _stack_it{it} {}
  MemorySegment pop() { return _stack[_stack_it--]; }
  MemorySegment peek() { return _stack[_stack_it]; }
  void push(MemorySegment v) { _stack[_stack_it++] = v; }

private:
  Memory<Sz> &_stack;
  std::size_t &_stack_it;
};

template <std::size_t Sz>
using HostFunction = std::function<void(StackHandle<Sz>)>;

using Code =
    std::tuple<Opcode, optional<MemorySegment>, optional<MemorySegment>>;

} // namespace stackmachine::detail
