add_library(stackmachine INTERFACE)
target_include_directories(stackmachine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sm sm.cpp)
target_link_libraries(sm
  PUBLIC
  spdlog::spdlog
  stackmachine
  )
