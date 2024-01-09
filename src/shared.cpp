#include "shared.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

const std::string LOG_FILENAME = "output/runtime.log";

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

void init_log() {
    logging::add_common_attributes(); // anade data como TimeStamp
    logging::add_file_log(
        keywords::file_name = LOG_FILENAME,
        keywords::rotation_size = 10 * 1024 * 1024, // 10Mb
        keywords::format = "[%TimeStamp%]: %Message%"
    );

    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info
    );
}
