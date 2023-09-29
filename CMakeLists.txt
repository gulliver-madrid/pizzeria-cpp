cmake_minimum_required(VERSION 3.16)
project(pizzeria LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)


add_executable(pizzeria
    src/main.cpp
    src/actualizar_iu.cpp
    src/cadenas.cpp
    src/datos_niveles.cpp
    src/debug.cpp
    src/juego.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo.cpp
    src/nivel.cpp
    src/setup_juego.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/vista/botones.cpp
    src/vista/componentes.cpp
    src/vista/etiquetas.cpp
    src/vista/grid.cpp
    src/vista/vista.cpp
    src/vista/vista_basics.cpp
    src/demos/demo_nivel.cpp
    src/demos/map.cpp
    src/demos/unicode.cpp
    src/demos/visual.cpp
    src/demos/visual_textos.cpp
)
target_link_libraries(pizzeria PRIVATE sfml-graphics sfml-audio)
target_compile_features(pizzeria PRIVATE cxx_std_17)

# Tratar los warnings como errores en modo Debug.
if(MSVC)
    target_compile_options(pizzeria PRIVATE "$<$<CONFIG:Debug>:/WX>")
endif()


if(WIN32)
    add_custom_command(
        TARGET pizzeria
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:pizzeria>
        VERBATIM)
endif()

install(TARGETS pizzeria)

# Unit tests
enable_testing()
add_executable(
    runUnitTests

    # tests
    src/tests/test_main.cpp
    src/tests/test_cadenas.cpp
    src/tests/test_encargadas.cpp
    src/tests/test_evaluar_preparacion.cpp
    src/tests/test_tiempo.cpp

    # archivos del proyecto
    src/cadenas.cpp
    src/debug.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo.cpp
    src/textos.cpp
    src/tiempo.cpp
)
target_link_libraries(runUnitTests PRIVATE sfml-graphics sfml-audio )
target_link_libraries(runUnitTests PUBLIC gtest gtest_main)
target_compile_features(runUnitTests PRIVATE cxx_std_17)
add_test(NAME runUnitTests COMMAND runUnitTests)
