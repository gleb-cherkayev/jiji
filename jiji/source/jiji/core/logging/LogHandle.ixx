export module jiji:core.logging.LogHandle;
import :prelude;
import :core.logging.LogTarget;
import :core.logging.Logger;


namespace jiji::core::logging {

/*
	Provides control over an individual log target.
	Does not own the target though, destroying the handle does not close the associated log target.
	May outlive the target safely.
*/
class LogHandle : noncopyable {
private:
	LogHandle() = default;

public:
	// Creates a handle for the given log.
	static unique_ptr<LogHandle> Create(shared_ptr<LogTarget> const& target) {
		if (!target) return nullptr;

		auto instance = unique_ptr<LogHandle>(new LogHandle);
		instance->target_ = target;
		return instance;
	}

// CLOSE
	// Closes the log target immediately, if it is still alive.
	void Close() {
		if (auto target = target_.lock())
			theLogger().Close(target);
		target_.reset();
	}

// OPTIONS
	// Message filtering. Everything is enabled by default.
//	void Enable(MessageLevel);
//	void Disable(MessageLevel);

private:
	weak_ptr<LogTarget> target_;
};

}  // jiji::core::logging
