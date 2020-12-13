foreach(test testStackHandle testStackMachine)
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test}
    PUBLIC
    spdlog::spdlog
    stackmachine
    GTest::gtest
    )
endforeach()
