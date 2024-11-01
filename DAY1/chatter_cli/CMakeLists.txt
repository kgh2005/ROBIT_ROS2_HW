cmake_minimum_required(VERSION 3.8)
project(chatter_cli)

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
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)  # Qt5 패키지 찾기
find_package(std_msgs REQUIRED)

# Build executable
add_executable(chatter_cli
  src/main.cpp
  src/talker.cpp
  src/listener.cpp
)

# Include directories
target_include_directories(chatter_cli PRIVATE include)

# Link dependencies
ament_target_dependencies(
  chatter_cli
  rclcpp
  std_msgs
)

# Qt 라이브러리 링크
target_link_libraries(chatter_cli Qt5::Core Qt5::Widgets)

# Install target
install(TARGETS
  chatter_cli
  DESTINATION lib/${PROJECT_NAME}
)

# Testing dependencies and setup
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
