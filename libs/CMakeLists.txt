add_subdirectory(glfw)
add_subdirectory(glew)
add_subdirectory(glm)
set_target_properties(libglew_shared PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

