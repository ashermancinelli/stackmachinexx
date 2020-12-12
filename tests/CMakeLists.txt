add_executable(testStackMachine testStackMachine.cpp)
add_executable(testStackHandle testStackHandle.cpp)

foreach(test testStackMachine testStackHandle)
target_link_libraries(${test
  PRIVATE
  StackMachine
  GTest::gtest
  )
endforeach()
