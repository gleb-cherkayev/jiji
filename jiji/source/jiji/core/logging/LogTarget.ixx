export module jiji:core.logging.LogTarget;
import :prelude;


namespace jiji::core::logging {

/*
	Encapsulates a single logging destination.
*/
class LogTarget : noncopyable {
public:
	// Managed with shared_ptr, to allow weak-referencing by LogHandle.
	static shared_ptr<LogTarget> Open(/*unique_ptr<LogSink>*/) {
//		if (!sink) return nullptr;

		auto instance = shared_ptr<LogTarget>(new LogTarget);
//		instance->sink_ = std::move(sink);
		instance->filter_ = Filter::Create();
		return instance;
	}

	// Provides identification for the log.
	string_view target_name() const {
//		return sink_->name();
		return "";
	}

// WRITE
	// Write full message to log.
//	void WriteLine(Message const&);
	// Write a message to log, but don't end the line
//	void WritePrefix(Message const&);
	// Finalise the line with status.
//	void WriteSuffix(string_view, MessageLevel);

private:
	LogTarget();

private:
	// Actual message destination.
//	unique_ptr<LogSink> sink_;
	// Filter to determine if the message should be passed.
	class Filter;
	unique_ptr<Filter> filter_;


	class Filter {
	public:
		static unique_ptr<Filter> Create();

//		void Enable(MessageLevel);
//		void Disable(MessageLevel);

		// Returns true if the filter passes such message through.
//		bool Accepts(MessageSource, MessageLevel) const;

	private:
		// Everything is enabled by default.
		uint levels_ = ~0u;
	};
};





}  // jiji::core::logging
