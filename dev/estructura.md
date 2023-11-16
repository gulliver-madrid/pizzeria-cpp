# Estructura del proyecto

- main.cpp
    - juego.h (hoja)

- controlador_clicks.cpp
    - controlador_clicks.h (hoja)
    - comandos.h
        - modelo/dominio.h (hoja)
    - estado_nivel.h (def)
    - general.h (hoja)
    - globales.h (hoja)
    - realizador_base.h (hoja)
    - vista/botones_app.h (def)

- datos_niveles.cpp
    - datos_niveles.h (def)
        - modelo/datos_nivel.h
            - modelo/control_pizzas.h (def)
    - setup_juego.h (hoja)
    - textos.h
        - textos.cpp
            - vista/cadenas.h (hoja)

- estado_nivel.cpp
    - estado_nivel.h
        - modelo/control_pizzas.h (def)
        - modelo/encargos.h (def)
    - general.h (hoja)
    - modelo/datos_nivel.h (hoja)

- globales.cpp
    - globales.h (hoja)
    - vista/componentes/boton_con_texto.h (def)

- juego.cpp
    - juego.h
    - datos_niveles.h (def)
    - globales.h (hoja)
    - nivel.h
        - globales.h (hoja)
        - shared.h (hoja)
        - tiempo.h (def)
        - vista/grid.h (hoja)
    - setup_juego.h (hoja)
    - textos.h (def)
    - vista/grid.h (hoja)

- modelo/control_pizzas.cpp
    - modelo/control_pizzas.h
          - shared.h (hoja)
          - modelo/modelo.h
              - modelo/dominio.h (hoja)

- modelo/dominio.cpp
    - modelo/dominio.h (hoja)

- modelo/encargos.cpp (hoja)
    - modelo/encargos.h
        - tiempo.h
            - templates.h (hoja)
    - modelo/dominio.h (hoja)

- modelo/modelo.cpp
    - modelo/modelo.h (def)
    - modelo/encargos.h (def)

- nivel.cpp
    - nivel.h (def)
    - controlador_clicks.h (hoja)
    - estado_nivel.h (def)
    - general.h (hoja)
    - modelo/datos_nivel.h (hoja)
    - realizador_base.h (hoja)
    - tiempo.h (def)
    - vista/enlace_vista.h (hoja)
    - vista/vista.h
        - vista/botones_app.h
            - vista/componentes/boton_con_texto.h
                - vista/componentes/boton_data.h (hoja)
            - modelo/dominio.h (hoja)
        - vista/etiquetas.h
            - modelo/control_pizzas.h (def)
            - modelo/modelo.h (def)
            - shared.h (hoja)
        - vista/paneles.h
            - modelo/modelo.h (def)
            - vista/barras_progreso.h
                - vista/componentes/barra_progreso.h (hoja)
            - vista/componentes/varios.h (hoja)

- setup_juego.cpp
    - setup_juego.h (hoja)
    - vista/cadenas.h (hoja)
    - globales.h (hoja)
    - paths.h (hoja)
    - vista/vista_data.h (def)

- tiempo.cpp
    - tiempo.h (def)
    - juego_assert.h (hoja)

- vista/barras_progreso.cpp
    - vista/barras_progreso.h (def)
    - modelo/modelo.h (def)
    - vista/basicos_vista.h (hoja)

- vista/basicos_vista.cpp (hoja)
    - vista/basicos_vista.h (hoja)

- vista/botones_app.cpp
    - modelo/dominio.h (hoja)
    - vista/componentes/botones.h
        - vista/componentes/boton_con_texto.h (def)
    - vista/componentes/varios.h (hoja)
    - vista/basicos_vista.h (hoja)

- vista/cadenas.cpp
    - vista/cadenas.h (hoja)

- vista/componentes/barra_progreso.cpp
    - vista/componentes/barra_progreso.h (hoja)

- vista/componentes/boton_con_texto.cpp
    - vista/componentes/boton_con_texto.h (def)

- vista/componentes/botones.cpp
    - vista/componentes/botones.h (def)
    - vista/componentes/varios.h (hoja)

- vista/enlace_vista.cpp
    - vista/enlace_vista.h (hoja)
    - vista/vista.h (def)

- vista/etiquetas/etiquetas.cpp
    - vista/etiquetas/etiquetas.h (def)
    - vista/basicos_vista.h (hoja)
    - vista/cadenas.h (hoja)
    - vista/componentes/varios.h (hoja)
    - vista/etiquetas/etiquetas_barra_estado.h (hoja)
    - vista/etiquetas/etiquetas_contadores.h (def)
    - vista/etiquetas/etiquetas_info.h
        - shared.h (hoja)
    - vista/etiquetas/fabrica_etiquetas.h

- vista/etiquetas/etiquetas_barra_estado.cpp
    - vista/etiquetas/etiquetas_barra_estado.h (hoja)
    - tiempo.h (def)
    - vista/basicos_vista.h (hoja)
    - vista/cadenas.h (def)
    - vista/componentes/varios.h (hoja)

- vista/etiquetas/etiquetas_contadores.cpp
    - vista/etiquetas/etiquetas_contadores.h
        - general.h (hoja)
        - modelo/control_pizzas.h (def)
    - modelo/modelo.h (def)
    - shared.h (hoja)
    - vista/basicos_vista.h (hoja)
    - vista/componentes/varios.h (hoja)
    - vista/presentador.h (hoja)
    - vista/etiquetas/fabrica_etiquetas_contadores.h (hoja)

- vista/etiquetas/etiquetas_info.cpp
    - vista/etiquetas/etiquetas_info.h (def)

- vista/etiquetas/fabrica_etiquetas_contadores.cpp
    - vista/etiquetas/fabrica_etiquetas_contadores.h (hoja)
    - vista/basicos_vista.h (hoja)
    - vista/componentes/varios.h (hoja)

- vista/grid.cpp
    - vista/grid.h (hoja)

- vista/paneles.cpp
    - vista/paneles.h (def)
    - vista/cadenas.h (hoja)
    - vista/etiquetas/etiquetas.h (def)
    - vista/basicos_vista.h (hoja)

- vista/presentador.cpp
    - vista/presentador.h (hoja)
    - modelo/dominio.h (hoja)
    - modelo/modelo.h (def)

- vista/vista.cpp
    - vista/vista.h (def)
    - estado_nivel.h (def)
    - general.h (hoja)
    - vista/basicos_vista.h (hoja)
    - vista/grid.h (hoja)
    - vista/vista_data.h (hoja)


## Leyenda
(def) Dependencias definidas en otro lugar
(hoja) Nodo hoja (sin dependencias dentro del proyecto)

## Criterios
- Se mantiene el orden de los includes en el código fuente.
- Los .cpp se consideran dependencias de los .h.
- Los .cpp se muestran en último lugar en la lista de dependencias.
- Se definen las dependencias solo de la primera aparición de un archivo.
