#pragma once

#include <string>

std::string interpolar(std::string plantilla);
std::string replace_placeholder(
    const std::string &template_str, const std::string &key,
    const std::string &value
);
