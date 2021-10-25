export module jiji:core.logging.LogTarget;
import :prelude;
import :core.logging.sinks.LogSink;


namespace jiji::core::logging {

/*
	Encapsulates a single logging destination.
*/
class LogTarget : noncopyable {
public:
	// Managed with shared_ptr, to allow weak-referencing by LogHandle.
	static shared_ptr<LogTarget> Open(unique_ptr<LogSink> sink) {
		if (!sink) return nullptr;

		auto instance = shared_ptr<LogTarget>(new LogTarget);
		instance->sink_ = std::move(sink);
		instance->filter_ = Filter::Create();  // Never fails
		return instance;
	}

// PROPERTIES
	// Provides identification for the log.
	string_view target_name() const {
		return sink_->name();
	}

	/*
		Helper class responsible for configuring which messages are passed to the sink.
		Everything is enabled by default.
	*/
	class Filter {
	public:
		static unique_ptr<Filter> Create() {
			return unique_ptr<Filter>(new Filter);
		}

	// OPTIONS
		// Enables logging of the messages of the given severity.
		void Enable(MessageLevel level) {
			levels_ |= to_mask_value(level);
		}
		// Disables logging of the messages of the given severity.
		void Disable(MessageLevel level) {
			levels_ &= ~to_mask_value(level);
		}

		// Returns true if the message should pass the filter.
		bool Accepts(Message const& message) const {
			return to_mask_value(message.level);
		}

	private:
		// Accepted message levels (all by default).
		uint levels_ = ~0u;
	};

	// Gives access to the target's message filter for configuration.
	Filter& filter() { return *filter_; }

// WRITE
	void WriteLine(Message const& message) {
		if (filter_->Accepts(message))
			sink_->Write(message);
	}

private:
	LogTarget() = default;

private:
	// Actual message destination.
	unique_ptr<LogSink> sink_;
	// Filter to determine if the message should be passed.
	unique_ptr<Filter> filter_;
};

}  // jiji::core::logging
