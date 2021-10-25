export module jiji:core.logging.routines;
import :prelude.no_logging;
import :core.logging.Message;

/*
	The following logging functions are available (residing in `jiji` namespace):
	- `log_error` (but prefer JIJI_LOG_ERROR instead of calling directly)
	- `log_warning` (but prefer JIJI_LOG_WARNING instead of calling directly)
	- `log_high`
	- `log_bold`
	- `log`
	- `log_loading`
	- `log_detail`
	- `log_comment` (used to implement JIJI_COMMENT_HERE macro, and should not be used directly)
	- `trace` (no-op in Ship build)
	See `Message.ixx` for the description of logging levels.
	All of them take as arguments formatting string (for std::format), and optionally, parameters to that string.

	`log_double_separator()` outputs decorative horizontal line (of equal signs) with Bold level.
	`log_single_separator()` does the same with dash symbols and Log level.

	`trace_here()` and `comment_here()` output formatted location of call site, but macros JIJI_TRACE_HERE and
		JIJI_COMMENT_HERE should be typically used instead of calling them directly (see `logging.hxx`).

	All these logging functions return an instance of special `jiji::core::logging::log_token` class.
*/


namespace jiji::core::logging {

/*
	Trivial type used to mark logging function call(used by logging "operations").
*/
struct log_token {};


// Helper internal function to hide dependency on Logger.
void _send_to_logger(Message&&);


//	General implementation for all logging functions.
template<MessageLevel level, typename... Args>
log_token _impl_log(string_view pattern, Args&&... args) {
	Message message{
		.text = std::format(pattern, std::forward<Args>(args)...),
		.level = level
	};

	_send_to_logger(std::move(message));
	return {};
}


// 0         1         2         3         4         5         6         7
// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
// 20:22:59 [***] ================================================================ 
const char* _double_line = "================================================================";
const char* _single_line = "----------------------------------------------------------------";

}  // jiji::core::logging


namespace jiji {

using namespace jiji::core::logging;

#define JIJI_LOG_FUNCTION(log_xxx, XXX) \
template<typename... Args> \
log_token log_xxx(string_view pattern, Args&&... args) { \
	return _impl_log<MessageLevel::XXX>(pattern, std::forward<Args>(args)...); \
}

// Logging routines for different message severities.
JIJI_LOG_FUNCTION(log_error, Error)
JIJI_LOG_FUNCTION(log_warning, Warning)
JIJI_LOG_FUNCTION(log_high, High)
JIJI_LOG_FUNCTION(log_bold, Bold)
JIJI_LOG_FUNCTION(log, Log)
JIJI_LOG_FUNCTION(log_loading, Loading)
JIJI_LOG_FUNCTION(log_detail, Detail)
JIJI_LOG_FUNCTION(log_comment, Comment)
#ifndef NDEBUG
JIJI_LOG_FUNCTION(trace, Debug)
#else
log_token trace(string_view pattern, Args&&... args) {
	return {};
}
#endif

#undef JIJI_LOG_FUNCTION


// Separators.
auto log_double_separator() {
	return log_bold(_double_line);
}

auto log_single_separator() {
	return log(_single_line);
}


// Location markers.
auto trace_here(std::source_location location) {
	return trace("{}() at {}:{}", location.function_name(), location.file_name(), location.line());
}

auto comment_here(std::source_location location) {
	return log_comment("{}() at {}:{}", location.function_name(), location.file_name(), location.line());
}

}  // jiji
