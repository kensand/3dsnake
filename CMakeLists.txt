cmake_minimum_required (VERSION 2.6)
project (3dSnake)


include_directories(include)

file(GLOB SOURCES "src/*.c*")

# add the executable
add_executable(3dsnake ${SOURCES})
target_link_libraries(3dsnake dl glfw GL glut GLEW GLU)
