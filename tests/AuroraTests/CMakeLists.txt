add_executable(AuroraTests
    main.cpp
    ../../external/miniaudio/miniaudio.c
)

target_link_libraries(AuroraTests
    PRIVATE
        aurora
)

target_include_directories(AuroraTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/external/miniaudio
)

add_test(
    NAME AuroraTests
    COMMAND AuroraTests
)