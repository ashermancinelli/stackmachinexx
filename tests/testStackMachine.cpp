#include <gtest/gtest.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/StackMachine.hpp>

using ::testing::InitGoogleTest;
using namespace stackmachine;
using types::Opcode;

TEST(StackMachine, StaticInitialization)
{
  constexpr std::size_t sz = 1024;
  using sm_t = StackMachine<sz>;
  typename sm_t::Stack stack;
  EXPECT_TRUE(stack.size() == sz);
}

TEST(StackMachine, Allocation)
{
  constexpr std::size_t ss = 2048;
  constexpr std::size_t hs = 2048;
  StackMachine sm;
  auto mem = sm.allocate(2048);
  EXPECT_TRUE(mem == std::nullopt);

  mem = sm.allocate(1024);
  EXPECT_FALSE(mem == std::nullopt) << "Unable to allocate memory on heap!";
}

TEST(StackMachine, ExecuteOp)
{
  StackMachine sm;
  sm.execute({
      {Opcode::Noop, {}, {}},
  });
}

TEST(StackMachine, HostFunctions)
{
  using MyStackMachine = StackMachine<32>;
  MyStackMachine sm;
  sm.registerFunction("printPop",
      [] (types::Memory<MyStackMachine::StackSize>& stack)
      {
        std::cout << stack[0] << "\n";
        return 0;
      });
}

TEST(StackMachine, ManualStore)
{
  StackMachine<16> sm;
  constexpr char original = 'a';
  constexpr char expected = 'b';
  auto _mem = sm.allocate(8);
  EXPECT_TRUE(_mem) << "Could not allocate heap memory!";

  auto mem = _mem.value();
  for (int i = 0; i < 8; mem++, i++)
  {
    *mem = expected;
  }
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  spdlog::set_level(spdlog::level::err);
  return RUN_ALL_TESTS();
}
