add_subdirectory(stackmachine)

add_executable(sm sm.cpp)
target_link_libraries(sm
  PRIVATE
  spdlog::spdlog
  StackMachine
  )
