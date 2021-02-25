
cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_BUILD_TYPE=DEBUG_CONFIGURATIONS)
project(car_detection)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

find_package(OpenCV 4.1 REQUIRED)

add_subdirectory(lib/pugixml)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(car_detection ${project_SRCS})
target_link_libraries(car_detection ${OpenCV_LIBRARIES} pugixml)