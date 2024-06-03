cmake_minimum_required(VERSION 3.5)
project(HelloGL VERSION 0.1.0)

# 使用 C++ 17 标准
set(CMAKE_CXX_STANDARD 17)

# 设置代码文件
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)

# 添加头文件
set(HEADER_DIR_GLAD ${PROJECT_SOURCE_DIR}/include/glad)
set(HEADER_DIR_GLFW ${PROJECT_SOURCE_DIR}/include/GLFW)
set(HEADER_DIR_KHR ${PROJECT_SOURCE_DIR}/include/KHR)
set(HEADER_DIR_GLM ${PROJECT_SOURCE_DIR}/include/glm)
set(HEADER_DIR_GLM_EXT ${PROJECT_SOURCE_DIR}/include/glm/ext)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
include_directories(${HEADER_DIR_GLAD} ${HEADER_DIR_GLFW} ${HEADER_DIR_KHR} ${HEADER_DIR_GLM} ${HEADER_DIR_GLM_EXT} ${LIB_DIR})

# 添加目标链接
set(GLFW_DYLIB ${LIB_DIR}libglfw.3.dylib)
set(GLFW_A ${LIB_DIR}libglfw3.a)
link_libraries(${GLFW_DYLIB} ${GLFW_A})

# 执行编译命令
set(SOURCES ${SRC_DIR}glad.c ${SRC_DIR}main.cpp ${SRC_DIR}Shader.cpp ${SRC_DIR}texture_builder.cpp)
add_executable(HelloGL ${SOURCES})

# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(HelloGL "-framework OpenGL")
endif()

# target_link_libraries(HelloGL "glm::glm-header-only")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

