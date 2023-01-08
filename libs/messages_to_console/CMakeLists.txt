add_library(messages_to_console
            messages_to_console.c)

target_link_libraries(messages_to_console
                      color_print)