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

	void Close(shared_ptr<LogTarget> const&) {
		// TODO
	}

// LOG
	void Consume(Message&& message) {
		message.text += '\n';
		for (auto& log : targets_)
			log->WriteLine(message);
	}

private:
	unique_ptr<LogHandle> _add(shared_ptr<LogTarget> const& log) {
		if (!log) return nullptr;

		//if (emit_internal_messages_)
		//	lili::log("Logger: Adding log: `%.*s`.", log->target_name().size(), log->target_name().data());

		targets_.push_back(log);

		//for (auto&& line : cached_messages_)
		//	if (log->filter().Accepts(line.source, line.level))
		//		log->WriteLine(line);

		//if (emit_internal_messages_) {
		//	Message message
		//	{
		//		.indent = 0,
		//		.source = MessageSource::System,
		//		.level = MessageLevel::Bold,
		//		.timestamp = this->get_current_time(),
		//		.body = this->create_opening_message()
		//	};
		//	log->WriteLine(message);
		//}

		return LogHandle::Create(log);
	}


private:
	// All active logs targets.
	std::vector<shared_ptr<LogTarget>> targets_;

	// Current indentation depth.
	int indent_ = 0;

	// Messages kept to be inserted into a newly added target.
//	std::vector<Message> cached_messages_;
	// Maximum number of messages to keep.
	uint max_cached_messages_;

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

}  // jiji::core::logging
