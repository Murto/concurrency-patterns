# Set minimum version
cmake_minimum_required(VERSION 3.7.2)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Set project
project(guarded_suspension LANGUAGES CXX)

# Include pthreads library
find_package(Threads)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(guarded_suspension ${SOURCES})

target_link_libraries(guarded_suspension ${CMAKE_THREAD_LIBS_INIT})

# Include include directory
target_include_directories(guarded_suspension
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Make warnings errors
target_compile_options(guarded_suspension PRIVATE -Werror)
