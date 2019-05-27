# Set minimum version
cmake_minimum_required(VERSION 3.7.2)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Set project
project(active_object LANGUAGES CXX)

# Include pthreads library
find_package(Threads)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(active_object ${SOURCES})

target_link_libraries(active_object ${CMAKE_THREAD_LIBS_INIT})

# Include include directory
target_include_directories(active_object
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Make warnings errors
target_compile_options(active_object PRIVATE -Werror)
