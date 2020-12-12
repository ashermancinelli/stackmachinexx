#include <gtest/gtest.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/StackMachine.hpp>

using ::testing::InitGoogleTest;
using namespace stackmachine;
using namespace stackmachine::detail;

TEST(StackHandle, ExecuteNoop)
{
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  spdlog::set_level(spdlog::level::err);
  return RUN_ALL_TESTS();
}
