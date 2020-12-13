#pragma once
#include <algorithm>
#include <map>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/Types.hpp>
#include <stackmachine/detail/StackImpl.hpp>
#include <string>
#include <vector>

using std::map;
using std::optional;
using std::string;
using std::vector;

namespace stackmachine
{

template <std::size_t StackSize = 2048> struct StackMachine
{
  using Memory = typename ::stackmachine::Memory<StackSize>;

  constexpr StackMachine() noexcept = default;

  void registerFunction(string const &name, HostFunction f) noexcept
  {
    _ftable.insert({name, f});
  }

  void callFunction(string const &name)
  {
    spdlog::debug("INVOKE: {}", _ftable[name]);
    _ftable[name](_stack);
  }

  /** Executes a vector of instructions on the stack machine.  */
  void execute(const vector<Code> &code)
  {
    for (auto const &inst : code)
    {
      execute(inst);
    }
  }

  /** Execute a single instruction */
  void execute(Code) {}

  bool hasError() const
  {
    return false;
  }

private:
  /** Process id */
  std::size_t _pid = 0;

  /** Dynamic function lookup table for host functions */
  std::unordered_map<string, HostFunction> _ftable;

  /** Internal stack handle */
  ::stackmachine::detail::StackHandleImpl<StackSize> _stack;
};

} // namespace stackmachine
