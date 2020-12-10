#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/detail/Types.hpp>
#include <stackmachine/detail/StackImpl.hpp>
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
  std::size_t pid;

  using Stack = ::stackmachine::detail::Types::Memory<StackSize>;
  using HostFunction = ::stackmachine::detail::Types::HostFunction<StackSize>;
  using Code = ::stackmachine::detail::Types::Code;

  template<typename T>
  using Result = ::stackmachine::detail::Types::Result<T>;

  template<>
  using Result = ::stackmachine::detail::Types::Result<std::true_type>;

  constexpr StackMachine() noexcept : _stack_it{0}, pid{0} {}

  constexpr void registerFunction(string const &name, HostFunction f) noexcept
  {
    _ftable.insert({name, f});
  }

  Result callFunction(std::size_t idx)
  {
    spdlog::debug("Attempting to call function {}", _ftable_names[idx]);
    return _ftable[idx](_stack);
  }

  [[nodiscard]] auto allocate(std::size_t bytes) noexcept
      -> Result<typename Stack::iterator>
  {
    spdlog::debug("Attempting to allocate {}", bytes);
    if (bytes == 0)
    {
      return "Don't allocate zero bytes!";
    }
    else if (_stack_it + bytes >= _stack.size())
    {
      return "Could not allocate more bytes than exist on the stack!";
    }
    auto r = _stack.begin() + _stack_it;
    _stack_it += bytes;
    return r;
  }

  [[nodiscard]] constexpr Stack const &rawStack() const { return _stack; }

  /**
   * @brief Executes a vector of instructions on the stack machine.
   */
  Result execute(vector<Code> const &code)
  {
    for (auto const &instruction_tup : code)
    {
      ::stackmachine::detail::StackImpl::run(this, instruction_tup);
    }
    return std::true_type{};
  }

private:
  std::unordered_map<string, HostFunction> _ftable;
  Stack _stack;
  std::size_t _stack_it; ///> Pointer to next byte to be allocated on stack
};

} // namespace stackmachine
