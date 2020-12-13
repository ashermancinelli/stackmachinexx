#include <gtest/gtest.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <stackmachine/StackMachine.hpp>

using ::testing::InitGoogleTest;
using namespace stackmachine;

TEST(StackHandle, PushPop)
{
  constexpr std::size_t Sz = 16;
  constexpr ::stackmachine::MemorySegment expect = 10;

  ::stackmachine::detail::StackHandleImpl<Sz> sh;

  sh.push(expect);
  EXPECT_EQ(sh.pop(), expect);
  EXPECT_ANY_THROW(sh.pop());
}

TEST(StackHandle, Peek)
{
  constexpr std::size_t Sz = 16;
  constexpr ::stackmachine::MemorySegment expect = 10;

  ::stackmachine::detail::StackHandleImpl<Sz> sh;

  sh.push(expect);
  EXPECT_EQ(sh.peek(), expect);
  EXPECT_EQ(sh.pop(), expect);
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  spdlog::set_level(spdlog::level::err);
  return RUN_ALL_TESTS();
}
