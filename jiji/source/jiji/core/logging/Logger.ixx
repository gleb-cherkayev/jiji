export module jiji:core.logging.Logger;
import :prelude;
import :core.logging.LogHandle;
import :core.logging.sinks.DebuggerLogSink;


namespace jiji::core::logging {

class Logger : noncopyable {
private:
	Logger() {
		assert(!instance_);
		instance_ = this;
		// NOTE: After setting the instance.
		JIJI_COMMENT_HERE;
	}

public:
	~Logger() {
		JIJI_COMMENT_HERE;
		if (emit_internal_messages_)
			log_bold("All logs closed at {}.", format_current_date_time());

		assert(instance_ == this);
		instance_ = nullptr;
	}

	static unique_ptr<Logger> Create() {
		if (instance_) {
			JIJI_ERROR("Logger already created.");
			return nullptr;
		}

		return unique_ptr<Logger>(new Logger);
	}

// TARGETS
	unique_ptr<LogHandle> OpenDebuggerLog() {
		auto log = DebuggerLogSink::OpenLog();
		return this->_add(log);
	}

	// Closes the given log. Typically called through LogHandle.
	void Close(shared_ptr<LogTarget> const& target) {
		this->_close(target);
	}

// MESSAGES
	// Sends the message to the logs.
	void Consume(Message&& message) {
		this->_build(message);
		for (auto& target : targets_)
			target->WriteLine(message);
		if (cache_messages_) {
			if (cached_messages_.size() < max_cached_messages_)
				cached_messages_.push_back(std::move(message));
			else
				++overflown_messages_;
		}
	}

	// Stops caching of messages.
	// Caching is enabled at the start. This should be called internally after initial log target initialisation.
	void _stop_message_caching() {
		cache_messages_ = false;
		cached_messages_.clear();
		overflown_messages_ = 0;
	}

	// Changes the current message indentation level.
	// Normally, should only be used by `indent` class.
	void indent(int delta) {
		indent_ += delta;
	}

private:
	// Prepares the message before sending it to logs or storing, by adding extra information and formatting.
	void _build(Message& message) {
		static string temp;
		temp.clear();

		temp += format_time(message.timestamp);
		temp += ' ';

		temp += get_level_prefix(message.level);
		temp += ' ';

		for (int i = 0; i < indent_; ++i)
			temp += ". ";

		temp += get_level_message_prefix(message.level);
		temp += message.text;
		temp += '\n';
		std::swap(message.text, temp);
	}

	// Adds a new target internally, and perform accompanied logging, including dumping cached messages.
	unique_ptr<LogHandle> _add(shared_ptr<LogTarget> const& target) {
		if (!target) return nullptr;

		if (emit_internal_messages_)
			log("Adding log: `{}`.", target->target_name());

		targets_.push_back(target);

		for (auto&& line : cached_messages_)
			target->WriteLine(line);

		if (overflown_messages_) {
			Message message{
				.timestamp = get_current_time(),
				.text = std::format("<{} message(s) lost>", overflown_messages_),
				.level = MessageLevel::Log,
			};
			this->_build(message);
			target->WriteLine(message);
		}

		if (emit_internal_messages_) {
			// Only goes into this particular target.
			Message message{
				.timestamp = get_current_time(),
				.text = std::format("Log opened at {}.", format_current_date_time()),
				.level = MessageLevel::Bold,
			};
			this->_build(message);
			target->WriteLine(message);
		}

		return LogHandle::Create(target);
	}

	// Removes a target internally.
	void _close(shared_ptr<LogTarget> const& target) {
		if (!target) return;

		auto p = std::find(targets_.begin(), targets_.end(), target);
		if (p == targets_.end()) return;

		if (emit_internal_messages_) {
			// Only goes into this particular target.
			Message message{
				.timestamp = get_current_time(),
				.text = std::format("Log closed at {}.", format_current_date_time()),
				.level = MessageLevel::Bold,
			};
			this->_build(message);
			target->WriteLine(message);
		}

		targets_.erase(p);
	}

private:
	// All active logs targets.
	std::vector<shared_ptr<LogTarget>> targets_;

	// Current indentation depth.
	int indent_ = 0;

	// Messages kept to be inserted into a newly added target.
	std::vector<Message> cached_messages_;
	// Maximum number of messages to keep.
	size_t max_cached_messages_ = 16;
	// Messages not cached because of the limit, and lost.
	size_t overflown_messages_ = 0;

//	unique_ptr<Operations> operations_;

// CONTROLS
	// Controls whether the Logger should record messages for logging subsystems events,
	// such as adding or closing log target.
	bool emit_internal_messages_ = true;
	// Controls whether copies of written messages should be stored,
	// so that a later target would still receive them.
	bool cache_messages_ = true;

	// Singleton instance.
	static Logger* instance_;
	friend Logger& theLogger() {
		assert(logging::Logger::instance_);
		return *logging::Logger::instance_;
	}
};

Logger* Logger::instance_ = nullptr;
Logger& theLogger();


/*
	A helper class to perform scope-based log indentation for additional formatting.
	In most cases, (Quiet)OperationGuard would be preferred.
*/
class indent : noncopyable {
public:
	// Constructor. Increases log indentation.
	indent() {
		theLogger().indent(+1);
	}
	// Destructor. Decreases log indentation.
	~indent() {
		theLogger().indent(-1);
	}
};

}  // jiji::core::logging
