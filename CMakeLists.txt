cmake_minimum_required(VERSION 3.16)
project(BadEngine LANGUAGES CXX)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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

target_link_directories(BadEngine PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(BadEngine 
    PRIVATE 
        core 
        system 
        graphics 
)

if (WIN32)
    set_target_properties(BadEngine PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/ENTRY:mainCRTStartup"
    )
endif()

include(GNUInstallDirs)
install(TARGETS BadEngine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
