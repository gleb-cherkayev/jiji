#pragma once
#include <source_location>

/*
	Commonly used logging-related macros.
	NOTE: Macros don't have ending semicolon. Placing semicolon at calling site helps auto-formatter not to get confused.

	Use `JIJI_LOG_FUNCTION` and `JIJI_TRACE_FUNCTION` to log visiting a function, e.g. `[ * ] jiji::core::Core::~Core()`.
	Use `JIJI_COMMENT_HERE` and `JIJI_TRACE_HERE` to mark the precise location, e.g. `[ @ ] jiji::core::Core::~Core() at jiji\core\Core.ixx:34`.
	
	Prefer `JIJI_WARNING` and `JIJI_ERROR` for logging warnings and errors rather than direct `log_warning()` or `log_error()` calls,
	as they would also log error location in the code (via `JIJI_COMMENT_HERE`).

	See `logging.ixx` for other logging facilities.
*/


namespace jiji::core::logging {
// Formatting helpers for `std::source_location`.

// Removes parent directories from a file path under project tree up to the deepest `source` directory.
constexpr const char* trim_source_path(const char* path) {
	const char pattern[] = "\\source\\";
	auto start = string_view(path).rfind(pattern);
	if (start == std::string::npos)
		return path;
	return path + start + (sizeof(pattern) - 1);  // -1 for '\0'
}

// Modifies std::source_location to achieve desired representation in logs:
// - location path is stripped of uninteresting parent directories;
// - function name is optionally replaced (used to replace with __FUNCTION__);
consteval std::source_location trim(std::source_location location, const char* function_name = nullptr) {
	// HACK: Such (ab-)use of arguments is undocumented.
	return std::source_location::current(
		location.line(),
		location.column(),
		trim_source_path(location.file_name()),
		function_name ? function_name : location.function_name()
	);
}

}  // jiji::core::logging


// Location logging macros
// NOTE: __FUNCTION__ gives nicer output in comparison with `std::source_location::function_name()` (e.g., it included namespaces).
#define JIJI_LOG_FUNCTION log(__FUNCTION__)
#define JIJI_TRACE_FUNCTION trace(__FUNCTION__)

#define JIJI_COMMENT_HERE comment_here(jiji::core::logging::trim(std::source_location::current(), __FUNCTION__))
#define JIJI_TRACE_HERE trace_here(jiji::core::logging::trim(std::source_location::current(), __FUNCTION__))


// NOTE: Preferrable way for error reporting.
// These macros log warning or error, and include the location for more context.
#define JIJI_WARNING(...) JIJI_COMMENT_HERE; log_warning(__VA_ARGS__)
#define JIJI_ERROR(...) JIJI_COMMENT_HERE; log_error(__VA_ARGS__)
