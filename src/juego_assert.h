#include <stdexcept>

class JuegoException : public std::runtime_error {
  public:
    JuegoException(const std::string &mensaje) : std::runtime_error(mensaje) {}
};

inline void juego_assert(bool condicion, const std::string &mensaje = "") {
#ifdef _DEBUG
    if (!condicion) {
        throw JuegoException(
            mensaje.empty() ? std::string("Aserción no verificada") : mensaje
        );
    }
#endif
}
