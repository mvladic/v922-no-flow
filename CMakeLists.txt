cmake_minimum_required(VERSION 3.12)
project (v9-with-flow-no-eez-framework)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunused-const-variable -Wno-nested-anon-types -Wno-dollar-in-identifier-extension -O2 --no-entry -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-const-variable -Wno-nested-anon-types -Wno-dollar-in-identifier-extension -O2 --no-entry -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s INITIAL_MEMORY=83886080 -sLLD_REPORT_UNDEFINED -s USE_SDL=2")

set(USE_FLAGS "-s USE_SDL=2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s INITIAL_MEMORY=83886080 -sLLD_REPORT_UNDEFINED ${USE_FLAGS}")
add_definitions(-DEMCC_DEBUG)


include_directories(${PROJECT_SOURCE_DIR})

set(LV_CONF_BUILD_DISABLE_EXAMPLES 1)
set(LV_CONF_BUILD_DISABLE_DEMOS 1)
set(LV_CONF_BUILD_DISABLE_THORVG_INTERNAL 1)

add_subdirectory(lvgl)

file(GLOB MY_SOURCES "./*.c")
set(SOURCES ${MY_SOURCES})

file(GLOB_RECURSE my_src
    ./src/*.cpp
    ./src/*.c
)
list(APPEND SOURCES ${my_src})

add_executable(index ${SOURCES})

set(CMAKE_EXECUTABLE_SUFFIX ".html")

target_link_libraries(index
    lvgl
)

set_target_properties(index PROPERTIES LINK_FLAGS "--shell-file ${PROJECT_SOURCE_DIR}/index.html -s SINGLE_FILE=1")
