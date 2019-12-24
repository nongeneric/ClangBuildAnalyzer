cmake_minimum_required (VERSION 3.14)

project(ClangBuildAnalyzer LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(inih STATIC
    src/external/inih/ini.c
    src/external/inih/cpp/INIReader.cpp
)

add_library(llvm-demangle STATIC
    src/external/llvm-Demangle/lib/Demangle.cpp
    src/external/llvm-Demangle/lib/MicrosoftDemangleNodes.cpp
    src/external/llvm-Demangle/lib/MicrosoftDemangle.cpp
    src/external/llvm-Demangle/lib/ItaniumDemangle.cpp
)

add_executable(${PROJECT_NAME}
    src/Analysis.cpp
    src/BuildEvents.cpp
    src/Colors.cpp
    src/Utils.cpp
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} inih llvm-demangle)
