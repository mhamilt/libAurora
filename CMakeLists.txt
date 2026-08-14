cmake_minimum_required(VERSION 3.20)

project(Aurora
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# File Organisation
# ------------------------------------------------------------

file(GLOB_RECURSE AURORA_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

file(GLOB_RECURSE AURORA_HEADERS CONFIGURE_DEPENDS
    include/*.h
)

# ------------------------------------------------------------
# Static Library Source
# ------------------------------------------------------------

add_library(aurora STATIC)


target_sources(aurora
    
    PRIVATE

    # Library Headers
    ${AURORA_HEADERS}
    #include/Aurora/AcousticalParameters.h
    #include/Aurora/Audio.h
    #include/Aurora/audtypes.h
    #include/Aurora/aurora.h
    #include/Aurora/AuroraConvolver.h
    #include/Aurora/commdefs.h
    #include/Aurora/Complex.h
    #include/Aurora/Convolver.h
    #include/Aurora/Multivolver.h
    #include/Aurora/SineSweepGenerator.h
    #include/Aurora/Vector.h
    #include/Aurora/version.h
    #include/Aurora/KirkebyBase.h
    #include/Aurora/STI.h
    

    include/Aurora/Spectrum.h 
    include/Aurora/SCOctaveBandAnalysis.h 
    include/Aurora/AcParametersTrack.h 
    include/Aurora/AcTSchroederDecay.h 

    # Core mathematics and data structures
    src/core/Audio.cpp
    src/core/Complex.cpp
    src/core/DataHolder.h
    src/core/gpfuncts.cpp
    src/core/SCFirWin.cpp
    src/core/SCFirWin.h
    src/core/SCOctaveBandFilter.cpp
    src/core/SCOctaveBandFir.cpp
    src/core/SCOctaveBandFir.h
    src/core/SCSignalWindows.cpp
    src/core/SCSignalWindows.h
    src/core/Spectrum.cpp    
    src/core/Vector.cpp

    # Convolution
    src/convolution/Convolver.cpp
    src/convolution/Multivolver.cpp
    src/convolution/AuroraConvolver.cpp    

    # Kirkeby inversion
    src/kirkeby/Kirkeby.cpp
    

    # Signal generation
    src/sweep/SineSweepGenerator.cpp

    # Acoustical analysis
    src/acousticanalysis/AcousticalParameters.cpp
    src/acousticanalysis/AcParametersTrack.cpp
    src/acousticanalysis/AcParametersData.cpp
    src/acousticanalysis/AcTResults.cpp
    src/acousticanalysis/AcTSchroederDecay.cpp

    # Speech Transmission Index
    src/sti/ModulationTransferFunctionsTable.cpp
    src/sti/ModulationTransferFunctionsTable.h    
    src/sti/STI.cpp
    src/sti/STIData.h
    src/sti/STIResults.h
    src/sti/STIResults.cpp
    src/sti/STISpectrum.cpp
    src/sti/STISpectrum.h
    src/sti/STITrack.h
    src/sti/STITrack.cpp

    # Time history analysis
    src/timehistoryanalysis/ThAnalyzerData.cpp
    src/timehistoryanalysis/ThAnalyzerData.h
    src/timehistoryanalysis/ThAnalyzerTrack.cpp
    src/timehistoryanalysis/ThAnalyzerTrack.h
    src/timehistoryanalysis/TimeHistoryAnalyzer.cpp
    src/timehistoryanalysis/TimeHistoryAnalyzer.h

    # Cross Functions
    src/xfunctions/Correlator.cpp
    src/xfunctions/Correlator.h
    
    # Dependencies
    external/kissfft/kiss_fft.c
    external/kissfft/kiss_fftr.c
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "Source Files"
    FILES ${AURORA_SOURCES}
)

source_group(
    TREE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PREFIX "Header Files"
    FILES ${AURORA_HEADERS}
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
        #${CMAKE_CURRENT_SOURCE_DIR}/include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/kissfft
)

# ------------------------------------------------------------
# Compiler options
# ------------------------------------------------------------

target_compile_features(aurora
    PUBLIC
        cxx_std_17
)


# ------------------------------------------------------------
# Xcode organisation
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
# Library Install
# ------------------------------------------------------------

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# install(
#     TARGETS aurora
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )

#install(TARGETS aurora
#    EXPORT AuroraTargets
#    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

install(TARGETS aurora
    EXPORT AuroraTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT AuroraTargets
    FILE AuroraTargets.cmake
    NAMESPACE Aurora::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Aurora
)

configure_package_config_file(
    cmake/AuroraConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/AuroraConfig.cmake
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/Aurora
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/AuroraConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/AuroraConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/AuroraConfigVersion.cmake
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/Aurora
)