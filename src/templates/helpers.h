#pragma once

#include <map>

template <typename Key, typename Value>
bool has_key(const std::map<Key, Value> &mapeo, Key clave_a_buscar) {
    return mapeo.find(clave_a_buscar) != mapeo.end();
}

template <typename K, typename V>
V get_or(const std::map<K, V> &m, const K &key, const V &defaultValue) {
    typename std::map<K, V>::const_iterator it = m.find(key);
    if (it == m.end()) {
        return defaultValue;
    } else {
        return it->second;
    }
}

template <typename Contenedor, typename Elemento>
bool contiene(Contenedor contenedor, Elemento elemento) {
    return contenedor.find(elemento) != contenedor.end();
}

/* Ordena el iterable segun el criterio proporcionado */
template <typename Iterable, typename Condicion>
void ordenar_por_criterio(Iterable iterable, Condicion condicion) {
    std::sort(iterable.begin(), iterable.end(), condicion);
}
