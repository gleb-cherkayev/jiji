module;
#include <ctime>
export module jiji:core.logging.Message;
import :prelude.no_logging;

/*
	Class `Message` stores together a log message text and associated attributes
		of the message, such as time (TODO not yet) or severity.

	`MessageLevel` enumeration represents all severity levels in use,
		either used directly with logging routines, or auxillary ones, such as Success.
*/


namespace jiji::core::logging {

/*
	Message level / severity enumeration.
*/ 
enum class MessageLevel {
	// Success message.
	// Used for OK in operation messages.
	Success,
	// Failure report, some task has failed and had to stop prematurely.
	// log_error()
	Error,
	// Reports that some operation have failed or finished in unexpected fall-back way.
	// Can also be used to indicate unusual, or otherwise worth extra attention, state.
	// log_warning()
	Warning,
	// Important messages that need to stand out.
	// log_high()
	High,

	// Significant (and rare) messages.
	// log_bold()
	Bold,
	// Ordinary messages. Most common choice.
	// log()
	Log,

	// Resource loading messages.
	// log_loading()
	Loading,
	// Rare/verbose supplementing messages.
	// log_detail()
	Detail,
	// Code locations.
	Comment,

	// Debug-only diagnostic messages.
	// trace()
	Debug,
};

// Converts the given enumeration member to an or-able value.
uint to_mask_value(MessageLevel e) { return 1u << std::underlying_type_t<MessageLevel>(e); }


/*
	Keeps a single message to be logged and its associated attributes.
*/
struct Message {
	// Time when the message was emitted.
	std::tm timestamp;
	// Message body text _or_ formatted final text.
	string text;
	// Message severity level.
	MessageLevel level;
//	// Desired message indentation.
//	int indent = 0;  // Currently, handled by Logger itself.
};


// TIME

// Returns current (local) time.
std::tm get_current_time() {
	std::time_t now = std::time(nullptr);
	if ((std::time_t)(-1) == now) return {};
	std::tm* tm = std::localtime(&now);
	if (!tm) return {};
	return *tm;
}

string format_time(std::tm const& time) {
	char buffer[32];
	size_t count = std::strftime(buffer, sizeof(buffer), "%T", &time);  // e.g. `20:14:55`
	if (!count) return "";
	return string(buffer, count);
}

string format_date_time(std::tm const& time) {
	char buffer[32];
	size_t count = std::strftime(buffer, sizeof(buffer), "%F %T", &time);  // e.g. `2021-10-27 20:17:11`
	if (!count) return "";
	return string(buffer, count);
}

string format_current_date_time() {
	return format_date_time(get_current_time());
}


// TEXT

// Returns text prefix representing message severity category.
string_view get_level_prefix(MessageLevel level) {
	switch (level) {
	case MessageLevel::Error:
		return "[XXX]";
	case MessageLevel::Warning:
		return "[???]";
	case MessageLevel::High:
		return "[!!!]";

	case MessageLevel::Bold:
		return "[===]";
	case MessageLevel::Log:
		return "[ * ]";

	case MessageLevel::Loading:
		return "[ ~ ]";
	case MessageLevel::Detail:
		return "[ i ]";
	case MessageLevel::Comment:
		return "[ @ ]";

	case MessageLevel::Debug:
		return "[ . ]";

	default:
		return "[ % ]";
	}
}

// Returns extra caption, additionally inserted into logs for some message levels.
string_view get_level_message_prefix(MessageLevel level) {
	switch (level) {
	case MessageLevel::Error:
		return "ERROR: ";
	case MessageLevel::Warning:
		return "WARNING: ";

	default:
		return "";
	}
}

}  // jiji::core::logging
