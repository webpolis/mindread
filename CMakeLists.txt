cmake_minimum_required(VERSION 2.6)
project(MINDREAD)
## Target
# Add MacPorts
INCLUDE_DIRECTORIES(/opt/local/include)
LINK_DIRECTORIES(/opt/local/lib)
set(MINDREAD_SRCS ThinkGearStreamParser.c main.cpp)
add_executable(mindread ${MINDREAD_SRCS})
## Link libraries
set(BOOST_LIBS thread date_time system)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
target_link_libraries(mindread ${Boost_LIBRARIES})
find_package(Threads REQUIRED)
target_link_libraries(mindread ${CMAKE_THREAD_LIBS_INIT})