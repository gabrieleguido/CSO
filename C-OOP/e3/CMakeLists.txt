cmake_minimum_required(VERSION 2.8.3)
project(linked_lists)

add_library(lib SHARED
    linked_list.c 
    float_list.c   
    int_list.c 
    list_list.c 
)
add_executable(exec
    main.c
)
target_link_libraries(exec 
    lib 
)

