cmake_minimum_required(VERSION 3.16)
project(pizzeria LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_policy(SET CMP0144 NEW)

# mas mensajes de error
add_compile_options(/W4)


# SFML
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

# Boost
set(BOOST_ROOT $ENV{BOOST_ROOT})
set(BOOST_LIBRARYDIR "$ENV{BOOST_ROOT}/stage/lib")
find_package(Boost 1.82 REQUIRED COMPONENTS log filesystem)
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories(${BOOST_LIBRARYDIR})

# evitar bug en boost
# more info: https://github.com/microsoft/vcpkg/issues/22495#issuecomment-1012967084
add_definitions(-DBOOST_USE_WINAPI_VERSION=BOOST_WINAPI_VERSION_WIN7)

add_executable(pizzeria
    src/main.cpp
    src/controlador_clicks.cpp
    src/datos_niveles.cpp
    src/debug_sfml.cpp
    src/globales.cpp
    src/juego.cpp
    src/modelo/control_pizzas.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo_interno.cpp
    src/modelo/modelo.cpp
    src/modelo_amplio/aplicador.cpp
    src/modelo_amplio/modelo_amplio.cpp
    src/modelo_amplio/realizador.cpp
    src/nivel.cpp
    src/motor_nivel.cpp
    src/shared/font.cpp
    src/setup_juego.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/shared/log_init.cpp
    src/vista/barras_progreso.cpp
    src/vista/botones_app.cpp
    src/vista/botones_despachar.cpp
    src/vista/botones_encargar.cpp
    src/vista/cadenas.cpp
    src/vista/componente.cpp
    src/vista/componentes/barra_progreso.cpp
    src/vista/componentes/boton_con_texto.cpp
    src/vista/componentes/botones.cpp
    src/vista/componentes/crear_etiqueta.cpp
    src/vista/componentes/etiqueta.cpp
    src/vista/enlace_vista.cpp
    src/vista/etiquetas/etiquetas.cpp
    src/vista/etiquetas/etiquetas_barra_estado.cpp
    src/vista/etiquetas/etiquetas_pedidos.cpp
    src/vista/etiquetas/etiquetas_preparadas.cpp
    src/vista/etiquetas/etiquetas_info.cpp
    src/vista/etiquetas/fabrica_etiquetas_preparadas.cpp
    src/vista/grid.cpp
    src/vista/paneles.cpp
    src/vista/presentador.cpp
    src/vista/vista.cpp
    src/vista/basicos_vista.cpp
    src/demos/boost_log.cpp
    src/demos/demo_nivel.cpp
    src/demos/map.cpp
    src/demos/unicode.cpp
    src/demos/visual.cpp
    src/demos/visual_textos.cpp
)
target_link_libraries(pizzeria PRIVATE sfml-graphics sfml-audio Boost::log Boost::filesystem)

# esto es si estamos es modo dinamico (?)
add_definitions(-DBOOST_ALL_DYN_LINK)

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
    src/tests/modelo/test_encargadas.cpp
    src/tests/modelo/test_evaluar_preparacion.cpp
    src/tests/modelo/test_modelo_amplio.cpp
    src/tests/presentador/test_enlace_vista.cpp
    src/tests/presentador/test_presentador.cpp
    src/tests/presentador/test_activacion_botones.cpp
    src/tests/test_cadenas.cpp
    src/tests/test_componente.cpp
    src/tests/test_num_nivel.cpp
    src/tests/test_tiempo.cpp
    src/tests/test_timer.cpp
    src/tests/test_usecases.cpp

    # archivos del proyecto
    src/controlador_clicks.cpp
    src/datos_niveles.cpp
    src/debug_sfml.cpp
    src/globales.cpp
    src/juego.cpp
    src/modelo/control_pizzas.cpp
    src/modelo/dominio.cpp
    src/modelo/encargos.cpp
    src/modelo/modelo_interno.cpp
    src/modelo/modelo.cpp
    src/modelo_amplio/aplicador.cpp
    src/modelo_amplio/modelo_amplio.cpp
    src/modelo_amplio/realizador.cpp
    src/nivel.cpp
    src/motor_nivel.cpp
    src/setup_juego.cpp
    src/shared/font.cpp
    src/textos.cpp
    src/tiempo.cpp
    src/shared/log_init.cpp
    src/vista/barras_progreso.cpp
    src/vista/botones_app.cpp
    src/vista/botones_despachar.cpp
    src/vista/botones_encargar.cpp
    src/vista/cadenas.cpp
    src/vista/componente.cpp
    src/vista/componentes/barra_progreso.cpp
    src/vista/componentes/boton_con_texto.cpp
    src/vista/componentes/botones.cpp
    src/vista/componentes/crear_etiqueta.cpp
    src/vista/componentes/etiqueta.cpp
    src/vista/enlace_vista.cpp
    src/vista/etiquetas/etiquetas.cpp
    src/vista/etiquetas/etiquetas_barra_estado.cpp
    src/vista/etiquetas/etiquetas_pedidos.cpp
    src/vista/etiquetas/etiquetas_preparadas.cpp
    src/vista/etiquetas/etiquetas_info.cpp
    src/vista/etiquetas/fabrica_etiquetas_preparadas.cpp
    src/vista/grid.cpp
    src/vista/paneles.cpp
    src/vista/presentador.cpp
    src/vista/vista.cpp
    src/vista/basicos_vista.cpp
    src/demos/boost_log.cpp
    src/demos/demo_nivel.cpp
    src/demos/map.cpp
    src/demos/unicode.cpp
    src/demos/visual.cpp
    src/demos/visual_textos.cpp
)
target_link_libraries(runUnitTests PRIVATE sfml-graphics sfml-audio Boost::log Boost::filesystem)
target_link_libraries(runUnitTests PUBLIC gtest gtest_main)
target_compile_features(runUnitTests PRIVATE cxx_std_17)
add_test(NAME runUnitTests COMMAND runUnitTests)

# demo_prueba
add_executable(demo_prueba
    src/_pruebas/main.cpp
)
# target_link_libraries(demo_prueba PRIVATE sfml-graphics sfml-audio Boost::log Boost::filesystem)
target_compile_features(demo_prueba PRIVATE cxx_std_17)
