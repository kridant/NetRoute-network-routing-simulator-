cmake_minimum_required(VERSION 3.16)
project(NetRoute)

set(CMAKE_CXX_STANDARD 17)

# Use Homebrew sfml@2 (keg-only) so we don't pick up SFML 3 from the default prefix.
if(NOT DEFINED SFML2_ROOT)
    if(EXISTS "/opt/homebrew/opt/sfml@2")
        set(SFML2_ROOT "/opt/homebrew/opt/sfml@2")
    elseif(EXISTS "/usr/local/opt/sfml@2")
        set(SFML2_ROOT "/usr/local/opt/sfml@2")
    endif()
endif()
if(SFML2_ROOT)
    list(PREPEND CMAKE_PREFIX_PATH "${SFML2_ROOT}")
    message(STATUS "Using SFML 2 from: ${SFML2_ROOT}")
endif()

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(NetRoute
    src/main.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
    src/Visualizer.cpp
    src/UI.cpp
)

target_include_directories(NetRoute PRIVATE include)
if(SFML2_ROOT)
    # Prefer sfml@2 headers over SFML 3 if both are installed under /usr/local.
    target_include_directories(NetRoute BEFORE PRIVATE "${SFML2_ROOT}/include")
endif()

target_link_libraries(NetRoute sfml-graphics sfml-window sfml-system)

target_compile_definitions(NetRoute PRIVATE
    NETROUTE_ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

add_custom_command(TARGET NetRoute POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:NetRoute>/assets"
    COMMENT "Copying assets next to NetRoute executable")