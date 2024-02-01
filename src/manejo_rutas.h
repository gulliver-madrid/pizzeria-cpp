#pragma once

#include <filesystem>
#include <iostream>
#include <string>

// Siempre hay que definir NOMINMAX antes de incluir windows.h
#define NOMINMAX
#include <cstdlib>
#include <windows.h>

std::string narrow(const std::wstring &w_cadena) {
    size_t tamano = 0;
    // Primero obtenemos el tamaño necesario para el buffer.
    wcstombs_s(&tamano, nullptr, 0, w_cadena.c_str(), _TRUNCATE);
    std::string cadena(tamano, '\0');
    // Luego convertimos la cadena.
    wcstombs_s(&tamano, &cadena[0], tamano, w_cadena.c_str(), _TRUNCATE);
    return cadena;
};

// std::string narrow(const std::wstring &w_cadena) {
//     auto tamano = std::wcstombs(nullptr, w_cadena.c_str(), 0);
//     std::string cadena(tamano, '\0');
//     std::wcstombs(&cadena[0], w_cadena.c_str(), tamano);
//     return cadena;
// };

std::string obtener_ruta_ejecutable() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return narrow(std::wstring(buffer).substr(0, pos));
}

std::filesystem::path obtener_ruta_recurso(const std::string &ruta_relativa) {
    std::string ruta_ejecutable = obtener_ruta_ejecutable();
    std::cout << "Ruta del ejecutable: " << ruta_ejecutable << std::endl;
    std::filesystem::path ruta_recurso(ruta_ejecutable);
    ruta_recurso /= ruta_relativa; // Combina las rutas correctamente
    std::filesystem::path ruta_absoluta =
        std::filesystem::absolute(ruta_recurso);

    // Imprimir la ruta para diagnóstico
    std::cout << "Ruta del recurso: " << ruta_absoluta << std::endl;

    return ruta_absoluta;
}
