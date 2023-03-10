#include "Helium/HeliumPrecompiled.h"

heliumBegin

std::string Internal::format_stacktrace(const boost::stacktrace::stacktrace& trace) {
    std::stringstream ss;
    ss << trace;
    return ss.str();
}

template <>
void Internal::LogError() {
    auto trace = boost::stacktrace::stacktrace();
    spdlog::error("Assertion failed");
    spdlog::error("At");
    spdlog::error("{}", format_stacktrace(trace));
}

heliumEnd
