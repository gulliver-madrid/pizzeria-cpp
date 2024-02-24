- main.cpp:
    - juego.h
    - shared/dev.h
    - shared/font.h
    - shared/log_init.h

- controlador_clicks.cpp:
    - controlador_clicks.h
    - fase_nivel.h
    - globales.h
    - modelo_amplio/modelo_amplio.h
    - vista/botones/botones_app.h

- controlador_clicks.h:
    - modelo_amplio/comandos.h

- datos_nivel.h:
    - modelo/datos_modelo_interno.h

- datos_niveles.cpp:
    - datos_niveles.h
    - setup_juego.h
    - textos.h

- datos_niveles.h:
    - datos_nivel.h

- debug_sfml.cpp:
    - debug_sfml.h

- enlace_vista/enlace_vista.cpp:
    - enlace_vista/enlace_vista.h
    - enlace_vista/presentador.h
    - enlace_vista/presentador_paneles.h
    - fase_nivel.h
    - shared/log_init.h
    - templates/helpers.h
    - vista/paneles.h

- enlace_vista/enlace_vista.h:
    - modelo_amplio/modelo_amplio.h
    - observador_fase.h
    - vista/presentacion_vista.h
    - vista/vista.h

- enlace_vista/presentador.cpp:
    - enlace_vista/presentador.h
    - modelo/dominio.h
    - templates/helpers.h
    - tiempo.h
    - vista/cadenas.h
    - vista/vista_shared.h

- enlace_vista/presentador.h:
    - modelo/modelo.h
    - modelo/modelo_shared.h
    - vista/presentaciones.h
    - vista/vista_shared.h

- enlace_vista/presentador_paneles.h:
    - enlace_vista/presentador.h
    - modelo/modelo.h
    - modelo/modelo_interno.h

- globales.cpp:
    - globales.h
    - vista/componentes/boton_con_texto.h

- juego.cpp:
    - juego.h
    - datos_niveles.h
    - globales.h
    - motor_nivel.h
    - nivel.h
    - setup_juego.h
    - shared/log_init.h
    - textos.h
    - vista/grid.h

- modelo/control_pizzas.cpp:
    - modelo/control_pizzas.h
    - templates/helpers.h

- modelo/control_pizzas.h:
    - modelo/modelo.h
    - shared/font.h

- modelo/datos_modelo_interno.h:
    - modelo/control_pizzas.h

- modelo/dominio.cpp:
    - modelo/dominio.h
    - templates/helpers.h

- modelo/encargos.cpp:
    - modelo/encargos.h
    - modelo/dominio.h
    - modelo/modelo_info.h
    - shared/log_init.h
    - shared/types.h
    - templates/helpers.h

- modelo/encargos.h:
    - shared/types.h
    - tiempo.h

- modelo/modelo.cpp:
    - modelo/modelo.h
    - modelo/encargos.h
    - templates/helpers.h

- modelo/modelo.h:
    - modelo/dominio.h
    - modelo/modelo_shared.h
    - shared/types.h

- modelo/modelo_interno.cpp:
    - modelo/modelo_interno.h
    - modelo/datos_modelo_interno.h
    - modelo/modelo_info.h

- modelo/modelo_interno.h:
    - modelo/control_pizzas.h
    - modelo/datos_modelo_interno.h
    - modelo/encargos.h

- modelo_amplio/aplicador.cpp:
    - modelo_amplio/aplicador.h
    - fase_nivel.h
    - modelo_amplio/comandos.h
    - modelo_amplio/modelo_amplio.h
    - modelo_amplio/realizador.h
    - modelo_amplio/realizador_base.h

- modelo_amplio/comandos.h:
    - modelo/dominio.h

- modelo_amplio/modelo_amplio.cpp:
    - modelo_amplio/modelo_amplio.h
    - modelo_amplio/comandos.h
    - observador_fase.h

- modelo_amplio/modelo_amplio.h:
    - fase_nivel.h
    - modelo/datos_modelo_interno.h
    - modelo/modelo_interno.h

- modelo_amplio/realizador.cpp:
    - modelo_amplio/realizador.h
    - fase_nivel.h
    - modelo_amplio/modelo_amplio.h
    - shared/dev.h
    - shared/log_init.h

- modelo_amplio/realizador.h:
    - modelo_amplio/realizador_base.h

- modelo_amplio/realizador_base.h:
    - modelo/dominio.h

- motor_nivel.cpp:
    - motor_nivel.h
    - controlador_clicks.h
    - datos_nivel.h
    - fase_nivel.h
    - modelo_amplio/aplicador.h
    - shared/log_init.h
    - shared/num_nivel.h

- motor_nivel.h:
    - enlace_vista/enlace_vista.h
    - globales.h
    - modelo_amplio/modelo_amplio.h
    - shared/font.h
    - shared/num_nivel.h
    - tiempo.h
    - vista/grid.h
    - vista/vista.h

- nivel.cpp:
    - nivel.h
    - datos_nivel.h
    - motor_nivel.h
    - shared/log_init.h
    - shared/num_nivel.h

- nivel.h:
    - shared/num_nivel.h

- setup_juego.cpp:
    - setup_juego.h
    - globales.h
    - manejo_rutas.h
    - paths.h
    - shared/log_init.h
    - vista/cadenas.h
    - vista/vista_data.h

- shared/font.cpp:
    - shared/font.h

- shared/log_init.cpp:
    - shared/log_init.h

- tests/modelo/test_encargadas.cpp:
    - modelo/encargos.h
    - modelo/modelo.h

- tests/modelo/test_evaluar_preparacion.cpp:
    - modelo/encargos.h
    - modelo/modelo.h
    - tiempo.h

- tests/modelo/test_modelo_amplio.cpp:
    - datos_nivel.h
    - fase_nivel.h
    - modelo_amplio/aplicador.h
    - modelo_amplio/comandos.h
    - modelo_amplio/modelo_amplio.h

- tests/presentador/test_activacion_botones.cpp:
    - enlace_vista/enlace_vista.h
    - modelo/datos_modelo_interno.h
    - modelo/dominio.h
    - modelo/modelo_info.h
    - modelo/modelo_interno.h
    - vista/vista.h

- tests/presentador/test_presentador.cpp:
    - enlace_vista/presentador.h
    - modelo/datos_modelo_interno.h
    - modelo/dominio.h
    - vista/vista.h

- tests/test_cadenas.cpp:
    - vista/cadenas.h

- tests/test_componente.cpp:
    - vista/componentes/componente.h

- tests/test_main.cpp:
    - shared/log_init.h

- tests/test_num_nivel.cpp:
    - shared/num_nivel.h

- tests/test_tiempo.cpp:
    - tiempo.h

- tests/test_timer.cpp:
    - juego_assert.h
    - tiempo.h

- tests/test_usecases.cpp:
    - datos_niveles.h
    - globales.h
    - juego.h
    - modelo_amplio/aplicador.h
    - modelo_amplio/comandos.h
    - motor_nivel.h
    - setup_juego.h
    - vista/basicos_vista.h
    - vista/paneles.h
    - vista/vista.h

- tests/test_vista.cpp:
    - vista/vista.h

- textos.cpp:
    - textos.h
    - shared/log_init.h
    - vista/cadenas.h

- textos.h:
    - shared/font.h
    - shared/num_nivel.h

- tiempo.cpp:
    - tiempo.h
    - juego_assert.h
    - templates/helpers.h

- tiempo.h:
    - templates/comparable.h

- vista/barras_progreso.cpp:
    - vista/barras_progreso.h
    - vista/basicos_vista.h
    - vista/vista_data.h

- vista/barras_progreso.h:
    - vista/componentes/barra_progreso.h
    - vista/presentaciones.h
    - vista/vista_shared.h

- vista/basicos_vista.cpp:
    - vista/basicos_vista.h

- vista/botones/botones_app.cpp:
    - vista/botones/botones_app.h
    - modelo/dominio.h
    - shared/log_init.h
    - templates/helpers.h
    - vista/basicos_vista.h
    - vista/botones/datos_botones.h
    - vista/componentes/boton_con_texto.h
    - vista/componentes/botones.h
    - vista/componentes/crear_etiqueta.h

- vista/botones/botones_app.h:
    - modelo/dominio.h
    - vista/botones/botones_generales.h
    - vista/componentes/componente.h
    - vista/vista_shared.h

- vista/botones/botones_despachar.cpp:
    - vista/botones/botones_despachar.h
    - modelo/dominio.h
    - templates/helpers.h
    - vista/basicos_vista.h
    - vista/botones/datos_botones.h
    - vista/componentes/boton_con_texto.h
    - vista/componentes/botones.h

- vista/botones/botones_despachar.h:
    - vista/vista_shared.h

- vista/botones/botones_encargar.cpp:
    - vista/botones/botones_encargar.h
    - modelo/dominio.h
    - templates/helpers.h
    - vista/basicos_vista.h
    - vista/botones/datos_botones.h
    - vista/componentes/boton_con_texto.h
    - vista/componentes/botones.h

- vista/botones/botones_encargar.h:
    - vista/vista_shared.h

- vista/botones/botones_generales.cpp:
    - vista/botones/botones_generales.h
    - vista/basicos_vista.h
    - vista/componentes/botones.h

- vista/botones/botones_generales.h:
    - vista/vista_shared.h

- vista/cadenas.cpp:
    - vista/cadenas.h

- vista/componentes/barra_progreso.cpp:
    - vista/componentes/barra_progreso.h
    - templates/dibujar_elementos.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h

- vista/componentes/barra_progreso.h:
    - shared/font.h
    - vista/componentes/componente.h

- vista/componentes/boton_con_texto.cpp:
    - vista/componentes/boton_con_texto.h
    - shared/log_init.h
    - templates/dibujar_elementos.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h
    - vista/posiciones.h

- vista/componentes/boton_con_texto.h:
    - vista/componentes/boton_data.h
    - vista/componentes/componente.h
    - vista/posiciones.h

- vista/componentes/boton_data.h:
    - shared/font.h

- vista/componentes/botones.cpp:
    - vista/componentes/botones.h
    - vista/componentes/crear_etiqueta.h
    - vista/posiciones.h

- vista/componentes/botones.h:
    - vista/componentes/boton_con_texto.h
    - vista/vista_shared.h

- vista/componentes/componente.cpp:
    - vista/componentes/componente.h

- vista/componentes/componente.h:
    - shared/font.h

- vista/componentes/crear_etiqueta.cpp:
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h

- vista/componentes/crear_etiqueta.h:
    - shared/font.h

- vista/componentes/etiqueta.cpp:
    - vista/componentes/etiqueta.h
    - juego_assert.h
    - shared/font.h

- vista/componentes/etiqueta.h:
    - vista/componentes/componente.h

- vista/etiquetas/etiquetas.cpp:
    - vista/etiquetas/etiquetas.h
    - vista/basicos_vista.h
    - vista/cadenas.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h
    - vista/etiquetas/etiquetas_barra_estado.h
    - vista/etiquetas/etiquetas_info.h
    - vista/presentacion_vista.h
    - vista/presentaciones.h

- vista/etiquetas/etiquetas.h:
    - modelo/modelo_shared.h
    - vista/componentes/componente.h
    - vista/presentacion_vista.h
    - vista/presentaciones.h
    - vista/vista_shared.h

- vista/etiquetas/etiquetas_barra_estado.cpp:
    - vista/etiquetas/etiquetas_barra_estado.h
    - tiempo.h
    - vista/basicos_vista.h
    - vista/cadenas.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h

- vista/etiquetas/etiquetas_barra_estado.h:
    - shared/font.h
    - vista/componentes/componente.h
    - vista/presentaciones.h

- vista/etiquetas/etiquetas_info.cpp:
    - vista/etiquetas/etiquetas_info.h
    - shared/log_init.h
    - textos.h
    - vista/basicos_vista.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h

- vista/etiquetas/etiquetas_info.h:
    - shared/font.h
    - shared/num_nivel.h
    - vista/componentes/componente.h
    - vista/presentacion_vista.h

- vista/etiquetas/etiquetas_pedidos.cpp:
    - vista/etiquetas/etiquetas_pedidos.h
    - shared/log_init.h
    - templates/dibujar_elementos.h
    - templates/helpers.h
    - vista/basicos_vista.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h
    - vista/presentaciones.h
    - vista/vista_shared.h

- vista/etiquetas/etiquetas_pedidos.h:
    - vista/componentes/componente.h
    - vista/vista_shared.h

- vista/etiquetas/etiquetas_preparadas.cpp:
    - vista/etiquetas/etiquetas_preparadas.h
    - modelo/dominio.h
    - shared/log_init.h
    - templates/dibujar_elementos.h
    - templates/helpers.h
    - vista/componentes/etiqueta.h
    - vista/etiquetas/fabrica_etiquetas_preparadas.h

- vista/etiquetas/etiquetas_preparadas.h:
    - modelo/control_pizzas.h
    - vista/componentes/componente.h
    - vista/vista_shared.h

- vista/etiquetas/fabrica_etiquetas_preparadas.cpp:
    - vista/etiquetas/fabrica_etiquetas_preparadas.h
    - vista/basicos_vista.h
    - vista/componentes/crear_etiqueta.h
    - vista/componentes/etiqueta.h

- vista/grid.cpp:
    - vista/grid.h
    - shared/types.h

- vista/paneles.cpp:
    - vista/paneles.h
    - shared/log_init.h
    - templates/dibujar_elementos.h
    - vista/basicos_vista.h
    - vista/botones/botones_despachar.h
    - vista/botones/botones_encargar.h
    - vista/componentes/boton_con_texto.h
    - vista/componentes/etiqueta.h
    - vista/etiquetas/etiquetas.h
    - vista/etiquetas/etiquetas_pedidos.h

- vista/paneles.h:
    - modelo/modelo.h
    - shared/font.h
    - vista/barras_progreso.h
    - vista/componentes/crear_etiqueta.h
    - vista/etiquetas/etiquetas_preparadas.h
    - vista/paneles_observables.h

- vista/presentaciones.h:
    - vista/cadenas.h

- vista/vista.cpp:
    - vista/vista.h
    - shared/dev.h
    - shared/log_init.h
    - templates/helpers.h
    - vista/basicos_vista.h
    - vista/botones/botones_app.h
    - vista/componentes/boton_con_texto.h
    - vista/etiquetas/etiquetas.h
    - vista/grid.h
    - vista/paneles.h
    - vista/vista_data.h

- vista/vista.h:
    - shared/num_nivel.h
    - vista/componentes/componente.h
    - vista/presentacion_vista.h
    - vista/presentaciones.h
    - vista/vista_shared.h

