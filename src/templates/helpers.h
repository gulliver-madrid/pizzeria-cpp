#pragma once

#include <map>

template <typename Key, typename Value>
bool has_key(const std::map<Key, Value> &mapeo, Key clave_a_buscar) {
    return mapeo.find(clave_a_buscar) != mapeo.end();
}
