#include "log_init.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <filesystem>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

void init_log() {
    auto core = logging::core::get();
#ifdef _DEBUG
    std::cout << "Habilitando logging" << std::endl;
    core->set_logging_enabled(true);
#else
    std::cout << "Deshabilitando logging" << std::endl;
    core->set_logging_enabled(false);
#endif
    std::filesystem::path logFileFolder =
        std::filesystem::current_path() / "logs";
    auto info_file = logFileFolder / "log_info_%N.log";
    auto debug_file = logFileFolder / "log_debug_%N.log";
    // Sink para mensajes de info y superiores
    logging::add_file_log(
        keywords::file_name = info_file,
        keywords::rotation_size = 100 * 1024, // Rotacion cada 100Kb
        keywords::max_files = 8,              //
        keywords::target = logFileFolder,     //
        keywords::filter = logging::trivial::severity >= logging::trivial::info,
        keywords::format = "[%TimeStamp%] [%Severity%]: %Message%"
    );

    // Sink para mensajes de debug
    logging::add_file_log(
        keywords::file_name = debug_file,
        keywords::rotation_size = 100 * 1024, // Rotacion cada 100Kb
        keywords::max_files = 8,              //
        keywords::target = logFileFolder,     //
        keywords::filter =
            logging::trivial::severity == logging::trivial::debug,
        keywords::format = "[%TimeStamp%]: %Message%"
    );

    logging::add_console_log(
        std::cout, keywords::format = "[%TimeStamp%] [%Severity%]: %Message%",
        keywords::filter =
            logging::trivial::severity >= logging::trivial::warning
    );

    // Atributos comunes
    logging::add_common_attributes();
}
