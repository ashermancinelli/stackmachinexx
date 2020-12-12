#include <gtest/gtest.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/StackMachine.hpp>

using ::testing::InitGoogleTest;
using namespace stackmachine;

TEST(StackMachine, ExecuteNoop)
{
  StackMachine sm;
  sm.execute({
      {::stackmachine::detail::Opcode::Noop, {}, {}},
  });
}

TEST(StackMachine, ExecutePush)
{
  StackMachine sm;
  sm.execute({
      {::stackmachine::detail::Opcode::Noop, {}, {}},
  });
}

TEST(StackMachine, RegisterFunc)
{
  constexpr std::size_t Sz = 16;
  StackMachine<Sz> sm;
  sm.registerFunction("PushTest",
      [] (StackMachine<Sz>::StackHandle h)
      {
        constexpr StackMachine<Sz>::MemorySegment expect = 10;
        h.push(expect);
        auto a = h.pop();
        EXPECT_TRUE(a == expect);
      });
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  spdlog::set_level(spdlog::level::err);
  return RUN_ALL_TESTS();
}
