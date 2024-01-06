#include "shared.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

const std::string LOG_FILENAME = "output/runtime.log";

namespace logging = boost::log;
namespace expr = boost::log::expressions;

void init_log() {
    logging::add_file_log(LOG_FILENAME);

    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info
    );
}
