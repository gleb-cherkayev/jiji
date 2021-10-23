export module jiji:core.logging.Message;
import :prelude.no_logging;


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


// Keeps a single message to be logged and its associated attributes.
struct Message {
	string text;
	MessageLevel level;
};


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

}
