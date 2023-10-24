cmake_minimum_required(VERSION 3.25)
project(ttt C)

set(CMAKE_C_STANDARD 11)

# directories for cunit
include_directories(${CMAKE_SOURCE_DIR}"C:/CUnit-2.1-2/CUnit/Headers")
link_directories("C:/CUnit-2.1-2/CUnit/Sources/.libs")

# executables
add_executable(ttt
    tictactoe.c
    ttt_test.c
)

# header files directory (same folder)
target_include_directories(ttt PRIVATE 
    ./
)

# more cunit things
set_target_properties(ttt PROPERTIES LINX_FLAGS -Wl,-lcunit)
target_link_libraries(ttt cunit)