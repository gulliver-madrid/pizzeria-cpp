- main.cpp:
    - juego.h

- aplicador.cpp:
    - aplicador.h
    - comandos.h
    - estado_nivel.h
    - realizador_base.h

- aplicador.h:
    - general.h

- comandos.h:
    - modelo/dominio.h

- controlador_clicks.cpp:
    - controlador_clicks.h
    - estado_nivel.h
    - general.h
    - globales.h
    - vista/botones_app.h

- controlador_clicks.h:
    - comandos.h

- datos_nivel.h:
    - modelo/datos_nivel_para_modelo.h

- datos_niveles.cpp:
    - datos_niveles.h
    - setup_juego.h
    - textos.h

- datos_niveles.h:
    - datos_nivel.h

- debug_sfml.cpp:
    - debug_sfml.h

- estado_nivel.cpp:
    - estado_nivel.h
    - datos_nivel.h
    - general.h

- estado_nivel.h:
    - modelo/estado_modelo.h

- globales.cpp:
    - globales.h
    - vista/componentes/boton_con_texto.h

- juego.cpp:
    - juego.h
    - datos_niveles.h
    - globales.h
    - nivel.h
    - setup_juego.h
    - textos.h
    - vista/grid.h

- modelo/control_pizzas.cpp:
    - modelo/control_pizzas.h

- modelo/control_pizzas.h:
    - modelo/modelo.h
    - shared.h

- modelo/datos_nivel_para_modelo.h:
    - modelo/control_pizzas.h
    - modelo/encargos.h

- modelo/dominio.cpp:
    - modelo/dominio.h

- modelo/encargos.cpp:
    - modelo/encargos.h
    - modelo/dominio.h

- modelo/encargos.h:
    - tiempo.h

- modelo/estado_modelo.cpp:
    - modelo/estado_modelo.h
    - modelo/datos_nivel_para_modelo.h

- modelo/estado_modelo.h:
    - modelo/control_pizzas.h
    - modelo/encargos.h

- modelo/modelo.cpp:
    - modelo/modelo.h
    - modelo/encargos.h

- modelo/modelo.h:
    - modelo/dominio.h

- modelo_amplio.h:
    - estado_nivel.h
    - general.h

- nivel.cpp:
    - nivel.h
    - aplicador.h
    - controlador_clicks.h
    - datos_nivel.h
    - estado_nivel.h
    - general.h
    - modelo_amplio.h
    - realizador_base.h
    - vista/enlace_vista.h
    - vista/vista.h

- nivel.h:
    - globales.h
    - shared.h
    - tiempo.h
    - vista/grid.h

- setup_juego.cpp:
    - setup_juego.h
    - globales.h
    - manejo_rutas.h
    - paths.h
    - vista/cadenas.h
    - vista/vista_data.h

- tests/modelo/test_encargadas.cpp:
    - modelo/encargos.h
    - modelo/modelo.h

- tests/modelo/test_evaluar_preparacion.cpp:
    - modelo/encargos.h
    - modelo/modelo.h

- tests/modelo/test_modelo_amplio.cpp:
    - comandos.h
    - datos_nivel.h
    - modelo_amplio.h

- tests/test_cadenas.cpp:
    - vista/cadenas.h

- tests/test_presentador.cpp:
    - modelo/dominio.h
    - modelo/modelo.h
    - vista/presentador.h

- tests/test_tiempo.cpp:
    - tiempo.h

- tests/test_timer.cpp:
    - juego_assert.h
    - tiempo.h

- textos.cpp:
    - textos.h
    - vista/cadenas.h

- textos.h:
    - shared.h

- tiempo.cpp:
    - tiempo.h
    - juego_assert.h

- tiempo.h:
    - templates.h

- vista/barras_progreso.cpp:
    - vista/barras_progreso.h
    - modelo/modelo.h
    - vista/basicos_vista.h
    - vista/vista_data.h

- vista/barras_progreso.h:
    - vista/componentes/barra_progreso.h

- vista/basicos_vista.cpp:
    - vista/basicos_vista.h

- vista/botones_app.cpp:
    - vista/botones_app.h
    - modelo/dominio.h
    - vista/basicos_vista.h
    - vista/componentes/botones.h
    - vista/componentes/varios.h

- vista/botones_app.h:
    - modelo/dominio.h
    - vista/componentes/boton_con_texto.h

- vista/cadenas.cpp:
    - vista/cadenas.h

- vista/componentes/barra_progreso.cpp:
    - vista/componentes/barra_progreso.h
    - shared.h
    - vista/componentes/varios.h

- vista/componentes/boton_con_texto.cpp:
    - vista/componentes/boton_con_texto.h
    - shared.h
    - vista/componentes/varios.h

- vista/componentes/boton_con_texto.h:
    - vista/componentes/boton_data.h
    - vista/componentes/componente.h

- vista/componentes/botones.cpp:
    - vista/componentes/botones.h
    - vista/componentes/varios.h

- vista/componentes/botones.h:
    - vista/componentes/boton_con_texto.h

- vista/componentes/varios.cpp:
    - vista/componentes/varios.h

- vista/enlace_vista.cpp:
    - vista/enlace_vista.h
    - vista/vista.h

- vista/etiquetas/etiquetas.cpp:
    - vista/etiquetas/etiquetas.h
    - vista/basicos_vista.h
    - vista/cadenas.h
    - vista/componentes/varios.h
    - vista/etiquetas/etiquetas_barra_estado.h
    - vista/etiquetas/etiquetas_contadores.h
    - vista/etiquetas/etiquetas_info.h

- vista/etiquetas/etiquetas.h:
    - modelo/control_pizzas.h
    - modelo/modelo.h
    - shared.h

- vista/etiquetas/etiquetas_barra_estado.cpp:
    - vista/etiquetas/etiquetas_barra_estado.h
    - tiempo.h
    - vista/basicos_vista.h
    - vista/cadenas.h
    - vista/componentes/varios.h

- vista/etiquetas/etiquetas_barra_estado.h:
    - shared.h

- vista/etiquetas/etiquetas_contadores.cpp:
    - vista/etiquetas/etiquetas_contadores.h
    - modelo/modelo.h
    - shared.h
    - vista/basicos_vista.h
    - vista/componentes/varios.h
    - vista/etiquetas/fabrica_etiquetas_contadores.h
    - vista/presentador.h

- vista/etiquetas/etiquetas_contadores.h:
    - general.h
    - modelo/control_pizzas.h

- vista/etiquetas/etiquetas_info.cpp:
    - vista/etiquetas/etiquetas_info.h
    - textos.h
    - vista/basicos_vista.h
    - vista/componentes/varios.h

- vista/etiquetas/etiquetas_info.h:
    - shared.h

- vista/etiquetas/fabrica_etiquetas_contadores.cpp:
    - vista/etiquetas/fabrica_etiquetas_contadores.h
    - vista/basicos_vista.h
    - vista/componentes/varios.h

- vista/etiquetas/fabrica_etiquetas_contadores.h:
    - shared.h

- vista/grid.cpp:
    - vista/grid.h

- vista/paneles.cpp:
    - vista/paneles.h
    - shared.h
    - vista/basicos_vista.h
    - vista/etiquetas/etiquetas.h

- vista/paneles.h:
    - modelo/modelo.h
    - shared.h
    - vista/barras_progreso.h
    - vista/componentes/varios.h

- vista/presentador.cpp:
    - vista/presentador.h
    - modelo/dominio.h
    - modelo/modelo.h

- vista/vista.cpp:
    - vista/vista.h
    - estado_nivel.h
    - general.h
    - vista/basicos_vista.h
    - vista/grid.h
    - vista/vista_data.h

- vista/vista.h:
    - vista/botones_app.h
    - vista/etiquetas/etiquetas.h
    - vista/paneles.h

