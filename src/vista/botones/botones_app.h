#pragma once

#include "../../modelo/dominio.h"
#include "../componentes/componente.h"
#include "../vista_shared.h"
#include "botones_generales.h"

class BotonConTexto;

class BotonesApp : public ComponenteConFont {
  private:
    std::vector<std::shared_ptr<BotonConTexto>> todos;
    void _establecer_todos();

  public:
    std::shared_ptr<BotonConTexto> empezar;
    // Solo para recibir input
    TipoPizzaToBoton &encargar;
    TipoPizzaToBoton &despachar;
    BotonesGenerales generales;

    // WARNING: podria haber algun error raro al liberar memoria segun el orden,
    // debido a que botones encargar es una referencia
    BotonesApp(
        const dominio::TiposDePizza &tp_disponibles,
        TipoPizzaToBoton &botones_encargar, //
        TipoPizzaToBoton &botones_despachar //
    );
    void mostrar_botones_nivel(bool nuevo_valor);
    virtual void set_font(const OptionalFont &new_font) override;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
