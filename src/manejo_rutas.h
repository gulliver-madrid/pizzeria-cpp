#pragma once

#include <filesystem>
#include <string>
#ifdef _WIN32
// Siempre hay que definir NOMINMAX antes de incluir windows.h
#define NOMINMAX
#include <cstdlib>
#include <windows.h>

std::string narrow(const std::wstring &w_cadena) {
    auto tamano = std::wcstombs(nullptr, w_cadena.c_str(), 0);
    std::string cadena(tamano, '\0');
    std::wcstombs(&cadena[0], w_cadena.c_str(), tamano);
    return cadena;
};
#elif __linux__
#include <limits.h>
#include <unistd.h>
#endif

std::string obtener_ruta_ejecutable() {
#ifdef _WIN32

    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return narrow(std::wstring(buffer).substr(0, pos));
#elif __linux__
    // TODO: test it in linux
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, pos);
    }
    return "";
#endif
}

std::filesystem::path obtener_ruta_recurso(const std::string &ruta_relativa) {
    std::string ruta_ejecutable = obtener_ruta_ejecutable();
    std::filesystem::path ruta_recurso(ruta_ejecutable);
    ruta_recurso /= ruta_relativa;
    return ruta_recurso;
}
