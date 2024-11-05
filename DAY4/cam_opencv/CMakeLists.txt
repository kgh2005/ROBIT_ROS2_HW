cmake_minimum_required(VERSION 3.5)
project(cam_opencv)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt 자동 처리 설정
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)  # 자동 MOC 설정
set(CMAKE_AUTORCC ON)  # 리소스 파일 자동 처리 설정

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(Boost 1.71.0 REQUIRED COMPONENTS thread)
find_package(Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
find_package(OpenCV REQUIRED)

# 소스 파일 및 헤더 파일 목록 생성
file(GLOB PRO_SOURCE_DIR src/*.cpp)
file(GLOB PRO_UI_DIR ui/*.ui)
file(GLOB PRO_INCLUDE_DIR include/${PROJECT_NAME}/*.hpp include/${PROJECT_NAME}/*.h)
file(GLOB PRO_RESOURCE_DIR resources/*.qrc)

# Qt 파일 래핑
qt5_wrap_ui(QT_UI_HPP ${PRO_UI_DIR})
qt5_wrap_cpp(QT_MOC_HPP ${PRO_INCLUDE_DIR})
qt5_add_resources(QT_RESOURCE_HPP ${PRO_RESOURCE_DIR})

# Include directories 설정
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 실행 파일 생성
add_executable(${PROJECT_NAME}
    ${PRO_SOURCE_DIR}
    ${QT_MOC_HPP}
    ${QT_UI_HPP}
    ${QT_RESOURCE_HPP}
)

# 타겟 의존성 추가
ament_target_dependencies(${PROJECT_NAME} rclcpp Boost sensor_msgs cv_bridge)

# 링크 라이브러리 설정
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network ${OpenCV_LIBRARIES})

# Include directories 설정 (target_include_directories 사용)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 설치 대상 설정
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# 빌드 테스트 설정
if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    ament_lint_auto_find_test_dependencies()
endif()

ament_package()
