# Estructura del proyecto (nuevo sistema)

- main.cpp
    - juego.h

- datos_niveles.cpp
    - datos_niveles.h (def)
        - general.h
            - modelo/control_pizzas.h
                - shared.h (hoja)
                - modelo/modelo.h
                    - modelo/dominio.h (hoja)
            - tiempo.h (def)
    - setup_juego.h
        - general.h (def)
    - textos.h
        - textos.cpp
            - vista/cadenas.h (hoja)

- globales.cpp
    - globales.h
        - vista/componentes/boton_con_texto.h (def)

- juego.cpp
    - juego.h
    - datos_niveles.h (def)
    - globales.h (def)
    - nivel.h
        - general.h (def)
        - vista/grid.h
    - setup_juego.h (def)
    - textos.h (def)
    - vista/grid.h (def)

- modelo/control_pizzas.cpp
    - modelo/control_pizzas.h (hoja)

- modelo/dominio.cpp
    - modelo/dominio.h (hoja)

- modelo/modelo.cpp
    - tiempo.h
        - templates.h (hoja)
    - modelo/encargos.h
        - tiempo.h (def)
        - modelo/encargos.cpp (hoja)
            - modelo/dominio.h (def)

- nivel.cpp
    - nivel.h (def)
    - estado_nivel.h (def)
    - tiempo.h (def)
    - vista/vista.h
        - vista/botones_app.h
            - vista/componentes/boton_con_texto.h
                - vista/componentes/boton_data.h (hoja)
            - modelo/dominio.h (hoja)
        - vista/etiquetas.h
            - general.h (def)
            - shared.h (hoja)
        - vista/paneles.h
            - modelo/modelo.h (def)
            - vista/barras_progreso.h
                - vista/componentes/barra_progreso.h (hoja)
            - vista/componentes/varios.h (hoja)

- setup_juego.cpp
    - setup_juego.h (def)
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
    - modelo/dominio.h
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

- vista/etiquetas/etiquetas.cpp
    - vista/etiquetas/etiquetas.h (def)
    - vista/basicos_vista.h (hoja)
    - vista/cadenas.h (hoja)
    - vista/componentes/varios.h (hoja)
    - vista/etiquetas/etiquetas_barra_estado.h (hoja)
    - vista/etiquetas/etiquetas_contadores.h
        - general.h (def)
    - vista/etiquetas/etiquetas_info.h
        - shared.h (hoja)
    - vista/etiquetas/fabrica_etiquetas.h

- vista/etiquetas/etiquetas_barra_estado.cpp
    - vista/etiquetas/etiquetas_barra_estado.h (hoja)
    - vista/basicos_vista.h (def)
    - vista/componentes/varios.h (hoja)

- vista/etiquetas/etiquetas_contadores.cpp
    - vista/componentes/varios.h (hoja)
    - vista/presentador.h (hoja)
    - vista/basicos_vista.h (hoja)
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
    - modelo/dominio.h (def)
    - modelo/modelo.h (def)

- vista/vista.cpp
    - vista/vista.h (def)
    - estado_nivel.h
        - general.h (def)
        - modelo/encargos.h (def)
    - vista/basicos_vista.h (hoja)
    - vista/grid.h (def)
    - vista/vista_data.h (hoja)


## Leyenda
(def) Dependencias definidas en otro lugar
(hoja) Nodo hoja (sin dependencias internas)

## Criterios
- Se mantiene el orden de los includes en el código fuente.
- Los .cpp se consideran dependencias de los .h.
- Los .cpp se muestran en último lugar en la lista de dependencias.
- Se definen las dependencias solo de la primera aparición de un archivo.
