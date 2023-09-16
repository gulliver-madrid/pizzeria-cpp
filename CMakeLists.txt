cmake_minimum_required(VERSION 3.16)
project(pizzeria LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(pizzeria
    src/main.cpp
    src/cadenas.cpp
    src/componentes.cpp
    src/debug.cpp
    src/grid.cpp
    src/juego.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/demos/map.cpp
    src/demos/unicode.cpp
    src/demos/visual.cpp
    src/demos/visual_textos.cpp
)
target_link_libraries(pizzeria PRIVATE sfml-graphics sfml-audio)
target_compile_features(pizzeria PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET pizzeria
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<BOOL:${ARCH_64BITS}>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:pizzeria>
        VERBATIM)
endif()

install(TARGETS pizzeria)
