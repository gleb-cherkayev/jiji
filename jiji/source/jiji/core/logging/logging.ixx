export module jiji:core.logging.logging;
import :prelude.no_logging;
import :core.logging.Message;

//import :core.logging.Logger;


namespace jiji::core::logging {

/*
	Trivial type used to mark logging function call(used by logging "operations").
*/
struct log_token {};


void pass_to_logger(Message const&);

/*
	Implementation for all logging functions.
*/
template<MessageLevel level, typename... Args>
log_token impl_log(string_view pattern, Args&&... args) {
	Message message{
		.text = std::format(pattern, std::forward<Args>(args)...),
		.level = level
	};

	pass_to_logger(message);

	return {};
}

template<typename... Args>
log_token log(string_view pattern, Args&&... args) {
	return impl_log<MessageLevel::Log>(pattern, std::forward<Args>(args)...);
}



#if 0
#define LILI_WRITE_LINE(source, level, format_pattern) \
if (the_log) \
{ \
	va_list args; \
	va_start(args, format_pattern); \
	the_log->WriteLine(source, level, vformat(format_pattern, args)); \
	va_end(args); \
} \
return log_token();




// Messages.
log_token log_error(const char*, ...) {
	std::format	
}

log_token log_warning(const char*, ...);
log_token log_bold(const char*, ...);
log_token log_high(const char*, ...);
log_token log(const char*, ...);
log_token log_loading(const char*, ...);
log_token log_detail(const char*, ...);
log_token log_comment(const char*, ...);
// NOTE: Does not produce any output if NDEBUG is in play.
log_token trace(const char*, ...);

// Separators.
void log_double_separator() {
	if (!the_log) return;
	the_log->WriteLine(LILI_CURRENT_MESSAGE_SOURCE, MessageLevel::Bold, double_line);
}

void log_single_separator() {
	if (!the_log) return;
	the_log->WriteLine(LILI_CURRENT_MESSAGE_SOURCE, MessageLevel::Log, single_line);
}
#endif
}
