#include "enlace_vista.h"
#include "vista.h"

void EnlaceVista::on_cambio_a_fase_activa() const {
    vista->mostrar_elementos_fase_activa();
}

void EnlaceVista::on_cambio_a_fase_espera_antes_de_resultado() const {
    vista->esconder_botones_gestion_pizzeria();
}
void EnlaceVista::esconder_paneles() const {
    vista->paneles_completos.visible = false;
}
