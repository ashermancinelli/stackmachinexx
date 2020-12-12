#pragma once
#include <algorithm>
#include <map>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/detail/StackImpl.hpp>
#include <stackmachine/detail/Types.hpp>
#include <string>
#include <vector>

using std::map;
using std::optional;
using std::string;
using std::vector;

namespace stackmachine
{

template <std::size_t StackSize = 2048> class StackMachine
{
  friend class ::stackmachine::detail::StackImpl;

public:
  using StackHandle = typename ::stackmachine::detail::StackHandle<StackSize>;
  using HostFunction = typename ::stackmachine::detail::HostFunction<StackSize>;
  using Memory = typename ::stackmachine::detail::Memory<StackSize>;
  using Code = ::stackmachine::detail::Code;

  constexpr StackMachine() noexcept : _stack_it{0}, pid{0} {}

  constexpr void registerFunction(string const &name, HostFunction f) noexcept
  {
    _ftable.insert({name, f});
  }

  void callFunction(std::size_t idx)
  {
    spdlog::debug("INVOKE: {}", _ftable[idx]);
    _ftable[idx](stackHandle());
  }

  /** Executes a vector of instructions on the stack machine.  */
  void execute(const vector<detail::Code> &code)
  {
    for (auto const &inst : code)
    {
      execute(inst);
    }
  }

  /** Execute a single instruction */
  void execute(detail::Code) {}

private:
  /** Process id */
  std::size_t pid;

  /** Dynamic function lookup table for host functions */
  std::unordered_map<string, HostFunction> _ftable;

  /** Raw memory array */
  Memory _stack;

  /** Pointer to next byte to be allocated on stack */
  std::size_t _stack_it;

  /** Shorthand for creating a handle to the stack */
  constexpr auto stackHandle()
  {
    return detail::StackHandle{_stack, _stack_it};
  }
};

} // namespace stackmachine
