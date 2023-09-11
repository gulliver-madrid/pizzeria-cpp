#include "juego.h"
#include "pruebas/demo_map.h"
#include <cassert>
#include <map>

#define APP 0

int main() { // fmt
    switch (APP) {
    case 1:
        return demo();
        break;

    default:
        assert(APP == 0);
        return juego();
        break;
    }
}
