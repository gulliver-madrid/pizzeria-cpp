#pragma once

#include <boost/log/trivial.hpp>

void init_log();

// Usa un nombre abreviado
#define LOG BOOST_LOG_TRIVIAL
