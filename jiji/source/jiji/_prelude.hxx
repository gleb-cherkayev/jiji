#pragma once

#include <cassert>

#include <type_traits>
#include <utility>

#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

#include <string>
using std::string;
#include <string_view>
using std::string_view;

#include <optional>
using std::optional;

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <format>

using uint = unsigned int;

#include <source_location>
#include <jiji/core/logging/logging.hxx>
