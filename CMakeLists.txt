cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME tilegame)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/tlg_main.c
	src/tlg_main_loop.c
	src/tlg_shader.c
	src/tlg_texture.c
	src/tlg_camera.c
	src/tlg_user_input.c
	src/tlg_vertex_types.c
	src/tlg_batch_renderer.c
	)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(external/cglm)
target_link_libraries(${PROJECT_NAME} PUBLIC cglm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

