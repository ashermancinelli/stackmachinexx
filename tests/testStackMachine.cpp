#include <gtest/gtest.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/StackMachine.hpp>

using ::testing::InitGoogleTest;
using namespace stackmachine;

TEST(StackMachine, ExecuteNoop)
{
  using ::stackmachine::Opcode;
  constexpr std::size_t Sz = 16;
  StackMachine<Sz> sm;
  sm.execute({
      {Opcode::Noop, {}, {}},
  });
  EXPECT_FALSE(sm.hasError());
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  spdlog::set_level(spdlog::level::err);
  return RUN_ALL_TESTS();
}
