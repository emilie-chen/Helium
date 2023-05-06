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
#include <algorithm>
#include <string_view>
#include <sstream>
#include <new>
#include <variant>
#include <optional>
#include <array>

using namespace std::literals::string_literals;
using namespace std::literals::chrono_literals;
using namespace std::literals::string_view_literals;

#include <boost/bimap.hpp>
#include <boost/intrusive_ptr.hpp>
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <boost/stacktrace.hpp>
#define BOOST_STACKTRACE_IN_USE
#endif
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <cppcoro/static_thread_pool.hpp>
#include <cppcoro/when_all.hpp>
#include <cppcoro/async_latch.hpp>
#include <cppcoro/async_mutex.hpp>
#include <cppcoro/generator.hpp>

#include "Helium/Core.h"
