add_subdirectory(glfw)
add_subdirectory(glew)
set_target_properties(libglew_shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

