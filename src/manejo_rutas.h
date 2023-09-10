#pragma once

#include <filesystem>
#include <string>
#ifdef _WIN32
// Siempre hay que definir NOMINMAX antes de incluir windows.h
#define NOMINMAX
#include <cstdlib>
#include <windows.h>

std::string narrow(const std::wstring &wstr)
{
    int len = std::wcstombs(nullptr, wstr.c_str(), 0);
    std::string str(len, '\0');
    std::wcstombs(&str[0], wstr.c_str(), len);
    return str;
};
#elif __linux__
#include <limits.h>
#include <unistd.h>
#endif

std::string getExePath()
{
#ifdef _WIN32

    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return narrow(std::wstring(buffer).substr(0, pos));
#elif __linux__
    // TODO: test it in linux
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");
        return std::string(buffer).substr(0, pos);
    }
    return "";
#endif
}

std::filesystem::path getResourcePath(const std::string &relativePath)
{
    std::string exePath = getExePath();
    std::filesystem::path resourcePath(exePath);
    resourcePath /= relativePath;
    return resourcePath;
}
