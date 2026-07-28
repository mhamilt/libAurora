# Find every immediate subdirectory
file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(TEST ${TEST_DIRS})

    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TEST})

        # Only create a target if it has a main.cpp
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/main.cpp)

            add_executable(${TEST})

            target_sources(${TEST}
                PRIVATE
                    ${TEST}/main.cpp
            )

            target_link_libraries(${TEST}
                PRIVATE
                    aurora
            )

            target_include_directories(${TEST}
                PRIVATE
                    ${PROJECT_SOURCE_DIR}/include
            )

            add_test(
                NAME ${TEST}
                COMMAND ${TEST}
            )

        endif()

    endif()

endforeach()