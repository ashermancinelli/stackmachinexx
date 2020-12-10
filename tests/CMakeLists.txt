add_executable(testStackMachine testStackMachine.cpp)
target_link_libraries(testStackMachine
  PRIVATE
  StackMachine
  GTest::gtest
  )
