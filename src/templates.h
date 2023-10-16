#pragma once

namespace templates {
    /* Permite que las clases derivadas obtengan todos los operadores de
     * comparación implementando únicamente < y ==
     */
    template <typename Derived> class Comparable {
      public:
        bool operator!=(const Derived &otro) const {
            return !static_cast<const Derived *>(this)->operator==(otro);
        }

        bool operator>(const Derived &otro) const {
            return otro < static_cast<const Derived &>(*this);
        }

        bool operator<=(const Derived &otro) const { return !(*this > otro); }

        bool operator>=(const Derived &otro) const { return !(*this < otro); }
        // Para permitir la llamada a la clase derivada
        virtual bool operator<(const Derived &other) const = 0;
    };
} // namespace templates
