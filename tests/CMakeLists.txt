# tests/CMakeLists.txt

file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

foreach(TEST ${TEST_DIRS})

    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TEST})

        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/CMakeLists.txt)
            add_subdirectory(${TEST})
        endif()

    endif()

endforeach()