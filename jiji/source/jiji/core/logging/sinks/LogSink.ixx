export module jiji:core.logging.sinks.LogSink;
import :prelude;


namespace jiji::core::logging {

class LogSink : noncopyable {
public:
	virtual ~LogSink() = default;

	// Provides identification for the log.
	virtual string_view name() const = 0;

	// Message writing implementation.
	virtual void Write(Message const&) = 0;
};

}
