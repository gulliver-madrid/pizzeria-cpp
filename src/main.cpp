#include "demos/map.h"
#include "juego.h"
#include <cassert>

#define APP 0

int main() { // fmt
    switch (APP) {
    case 1:
        return demo_map();
        break;

    default:
        assert(APP == 0);
        return juego();
        break;
    }
}
