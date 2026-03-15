cmake_minimum_required(VERSION 2.8.3)
project(linked_lists)

add_library(lib SHARED
    float_list.c   
    linked_list.c 
)
add_executable(exec
    main.c
)
target_link_libraries(exec 
    lib 
)

