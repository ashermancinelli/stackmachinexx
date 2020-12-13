#pragma once
#include <stackmachine/detail/Types.hpp>

namespace stackmachine::detail
{

/** Handle given to host functions and intrinsics */
template <std::size_t Sz> struct StackHandleImpl : StackHandle
{
  virtual StackHandle(Memory<Sz> &s, std::size_t &it) : _stack{s}, _stack_it{it}
  {
  }
  virtual MemorySegment pop() override { return _stack[_stack_it--]; }
  virtual MemorySegment peek() const override { return _stack[_stack_it]; }
  virtual void push(MemorySegment v) override { _stack[_stack_it++] = v; }

private:
  Memory<Sz> &_stack;
  std::size_t &_stack_it;
};

[[nodiscard]] static std::string Stringify(Opcode op)
{
  if (op == Opcode::Noop)
    return "Noop";
  else if (op == Opcode::Push)
    return "Push";
  else if (op == Opcode::Pop)
    return "Pop";
  else if (op == Opcode::Load)
    return "Load";
  else if (op == Opcode::Store)
    return "Store";
  else if (op == Opcode::Noop)
    return "Noop";
  throw std::runtime_error("Something has gone horribly wrong");
}

} // namespace stackmachine::detail
