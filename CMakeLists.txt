cmake_minimum_required(VERSION 3.16)

set(This CleanStrike)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)


enable_testing()

add_subdirectory(libs/googletest)

include_directories(include)
set(Headers
    include/CleanStrike/headers/Player.hpp
    include/CleanStrike/headers/CarromBoard.hpp
    include/CleanStrike/headers/Match.hpp
    include/CleanStrike/Player.cpp
    include/CleanStrike/CarromBoard.cpp
    include/CleanStrike/Match.cpp
    src/utils/removeSpaces.hpp
    src/utils/takeInput.hpp
)

file(COPY src/inputs DESTINATION .)
file(COPY logs DESTINATION .)

set(Sources
    src/main.cpp
    src/inputs/inputFile.txt
)


# configure_file(src/inputs/inputFile.txt {CMAKE_CURRENT_SOURCE_DIR})

add_executable(CleanStrikeMain ${Sources} ${Headers})

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)
