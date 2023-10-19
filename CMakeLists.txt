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
    src/datos_niveles.cpp
    src/debug_sfml.cpp
    src/globales.cpp
    src/juego.cpp
    src/modelo/control_pizzas.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo.cpp
    src/nivel.cpp
    src/setup_juego.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/vista/barras_progreso.cpp
    src/vista/botones_app.cpp
    src/vista/cadenas.cpp
    src/vista/componentes/barra_progreso.cpp
    src/vista/componentes/boton_con_texto.cpp
    src/vista/componentes/botones.cpp
    src/vista/componentes/varios.cpp
    src/vista/etiquetas/etiquetas.cpp
    src/vista/etiquetas/etiquetas_contadores.cpp
    src/vista/etiquetas/etiquetas_info.cpp
    src/vista/etiquetas/fabrica_etiquetas_contadores.cpp
    src/vista/grid.cpp
    src/vista/paneles.cpp
    src/vista/presentador.cpp
    src/vista/vista.cpp
    src/vista/basicos_vista.cpp
    src/demos/demo_nivel.cpp
    src/demos/map.cpp
    src/demos/prueba.cpp
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
    src/tests/test_presentador.cpp
    src/tests/test_tiempo.cpp
    src/tests/test_timer.cpp

    # archivos del proyecto
    src/debug_sfml.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/vista/cadenas.cpp
    src/vista/presentador.cpp
)
target_link_libraries(runUnitTests PRIVATE sfml-graphics sfml-audio )
target_link_libraries(runUnitTests PUBLIC gtest gtest_main)
target_compile_features(runUnitTests PRIVATE cxx_std_17)
add_test(NAME runUnitTests COMMAND runUnitTests)
