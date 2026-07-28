cmake_minimum_required(VERSION 3.20)

project(Aurora
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ------------------------------------------------------------
# Static library
# ------------------------------------------------------------

add_library(aurora STATIC)


target_sources(aurora
    PRIVATE

    # Core mathematics and data structures
    src/core/Audio.cpp
    src/core/Complex.cpp
    src/core/DataHolder.h
    src/core/gpfuncts.cpp
    src/core/gpfuncts.h
    src/core/SCFirWin.cpp
    src/core/SCFirWin.h
    src/core/SCOctaveBandFilter.cpp
    src/core/SCOctaveBandFilter.h
    src/core/SCOctaveBandFir.cpp
    src/core/SCOctaveBandFir.h
    src/core/SCSignalWindows.cpp
    src/core/SCSignalWindows.h
    src/core/Spectrum.cpp
    src/core/Spectrum.h
    src/core/Vector.cpp

    # Convolution
    src/convolution/Convolver.cpp
    src/convolution/Multivolver.cpp
    src/convolution/AuroraConvolver.cpp    

    # Kirkeby inversion
    #src/kirkeby/Kirkeby.cpp

    # Signal generation
    src/sweep/SineSweepGenerator.cpp

    # Acoustical analysis
    src/acousticanalysis/AcousticalParameters.cpp
    src/acousticanalysis/AcParametersTrack.cpp
    src/acousticanalysis/AcParametersData.cpp
    src/acousticanalysis/AcTResults.cpp
    src/acousticanalysis/AcTSchroederDecay.cpp

    # Speech Transmission Index
    #src/sti/SpeechTransmissionIndex.cpp

    # Time history analysis
    #src/timehistory/TimeHistoryAnalyzer.cpp
)


# ------------------------------------------------------------
# Optional test programmes
# ------------------------------------------------------------


option(AURORA_BUILD_TESTS "Build Aurora test programs" ON)

if(AURORA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


# ------------------------------------------------------------
# Public headers
# ------------------------------------------------------------

target_include_directories(aurora
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# ------------------------------------------------------------
# Compiler options
# ------------------------------------------------------------

target_compile_features(aurora
    PUBLIC
        cxx_std_17
)


# ------------------------------------------------------------
# Optional: nicer Xcode organisation
# ------------------------------------------------------------

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES
        ${AURORA_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES
        ${AURORA_HEADERS}
)


# ------------------------------------------------------------
# Installation (optional, useful later)
# ------------------------------------------------------------

include(GNUInstallDirs)

install(
    TARGETS aurora
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)