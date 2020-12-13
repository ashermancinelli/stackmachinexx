#pragma once
#include <exception>
#include <stackmachine/Types.hpp>

namespace stackmachine::detail
{

constexpr std::unordered_map<char, string> typemap{
    {0x7f, "i32"},     {0x7e, "i64"},  {0x7d, "f32"}, {0x7c, "f64"},
    {0x70, "anyfunc"}, {0x60, "func"}, {0x40, ""},
};

/** Handle given to host functions and intrinsics */
template <std::size_t Sz> struct StackHandleImpl : StackHandle
{
  StackHandleImpl() = default;

  virtual MemorySegment pop() override
  {
    if (_stack_it == 0)
      throw std::runtime_error("Popped an empty stack");
    return _stack[_stack_it--];
  }

  virtual MemorySegment peek() const override { return _stack[_stack_it]; }

  virtual void push(MemorySegment v) override
  {
    if (_stack_it == _stack.size() - 1)
      throw std::runtime_error("Pushed a full stack");
    _stack[++_stack_it] = v;
  }

private:
  Memory<Sz> _stack;
  std::size_t _stack_it = 0;
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
