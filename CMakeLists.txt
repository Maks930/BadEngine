cmake_minimum_required(VERSION 3.16)

project(BadEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


set(GLM_ENABLE_CXX_20 ON)
set(BUILD_SHARED_LIBS ON)

set(glew-cmake_BUILD_SHARED ON CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS  ON CACHE BOOL "" FORCE)
add_subdirectory(libs)

set(GLFW_BUILD_TESTS OFF)
# set(BUILD_SHARED_LIBS ON)

add_subdirectory(Engine)

include_directories(./Engine)

add_executable(BadEngine main.cpp)
target_link_libraries(BadEngine core system graphics)

include(GNUInstallDirs)
install(TARGETS BadEngine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
