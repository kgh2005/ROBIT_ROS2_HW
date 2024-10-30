cmake_minimum_required(VERSION 3.8)
project(turtlesim_cli)

# Enable compiler warnings for GNU and Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Build executable
add_executable(turtlesim_cli
  src/main.cpp
  src/turtlesim_cli.cpp
)

# Include directories
target_include_directories(turtlesim_cli PRIVATE include)

# Link dependencies
ament_target_dependencies(
  turtlesim_cli
  rclcpp
  turtlesim
  std_srvs
  geometry_msgs
)

# Install target
install(TARGETS
  turtlesim_cli
  DESTINATION lib/${PROJECT_NAME}
)

# Testing dependencies and setup
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Skip copyright check for this build
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
