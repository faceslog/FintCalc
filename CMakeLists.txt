cmake_minimum_required(VERSION 3.17)
project(asd2_univ_crypto)

# Create a list with all cpp source files
set (project_sources
        src/main.cpp
        src/fint.cpp)

# Create Executable with all necessary source files
add_executable(${PROJECT_NAME} ${project_sources})
