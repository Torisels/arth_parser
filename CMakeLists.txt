project(parser C)

set(CMAKE_C_STANDARD 99)

add_executable(parser main.c char_stack.c char_stack.h node_stack.c node_stack.h tree_printer.h expression_tree.h expression_tree.c)