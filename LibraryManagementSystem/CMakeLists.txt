cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(library_system
    src/main.cpp
    src/Book.cpp
    src/Member.cpp
    src/Library.cpp
)

# Ensure the executable is placed at the project root so relative
# paths like "data/books.txt" resolve correctly when run from there.
set_target_properties(library_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
