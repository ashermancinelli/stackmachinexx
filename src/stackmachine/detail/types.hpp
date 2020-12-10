#include <array>
#include <functional>
#include <optional>
#include <tuple>

namespace stackmachine::detail
{
using std::array;
using std::optional;
using std::tuple;

struct Types
{
  enum class Opcode
  {
    Noop = 0,
    Store,
    Load,
  };

  using MemorySegment = uint64_t;

  template <std::size_t Size> using Memory = array<MemorySegment, Size>;

  template <std::size_t StackSize>
  using HostFunction = std::function<Result(Memory<StackSize> &)>;

  using Code =
      std::tuple<Opcode, optional<MemorySegment>, optional<MemorySegment>>;

  template <typename ReturnT> using Result = std::variant<ReturnT, std::string>;
};

} // namespace stackmachine::detail
