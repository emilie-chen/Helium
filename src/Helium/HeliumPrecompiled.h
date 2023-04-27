#pragma once

#include <chrono>
#include <csignal>
#include <cstddef>
#include <filesystem>
#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <any>
#include <type_traits>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <semaphore>
#include <valarray>
#include <exception>

#include <boost/bimap.hpp>
#include <boost/intrusive_ptr.hpp>
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <boost/stacktrace.hpp>
#define BOOST_STACKTRACE_IN_USE
#endif
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <spdlog/spdlog.h>

#include "Helium/Core.h"
