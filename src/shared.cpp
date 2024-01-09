#include "shared.h"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace expr = boost::log::expressions;

void init_log() {
    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info
    );
}
