#include "Helium/HeliumPrecompiled.h"

heliumBegin

#if BOOST_STACKTRACE_IN_USE
std::string Internal::format_stacktrace(const boost::stacktrace::stacktrace& trace) {
    std::stringstream ss;
    ss << trace;
    return ss.str();
}
#endif

template <>
void Internal::LogError() {
#if BOOST_STACKTRACE_IN_USE
    auto trace = boost::stacktrace::stacktrace();
#endif
    spdlog::error("Assertion failed");
#if BOOST_STACKTRACE_IN_USE
    spdlog::error("At");
    spdlog::error("{}", format_stacktrace(trace));
#endif
}

heliumEnd
