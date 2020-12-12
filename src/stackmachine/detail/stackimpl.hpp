#pragma once
#include <stackmachine/detail/Types.hpp>

namespace stackmachine::detail
{

struct StackImpl
{
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
};

} // namespace stackmachine::detail
