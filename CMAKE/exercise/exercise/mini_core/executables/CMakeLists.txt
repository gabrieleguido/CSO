# TODO compile executable that will be run  
add_executable(many_object 
    many_object_in_stack_example.cpp
)
target_link_libraries(many_object
    core_library
)
