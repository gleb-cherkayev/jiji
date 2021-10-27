export module jiji:core.logging.LogHandle;
import :prelude;
import :core.logging.LogTarget;


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
	// Creates a handle for the given log target.
	static unique_ptr<LogHandle> Create(shared_ptr<LogTarget> const& target) {
		if (!target) return nullptr;

		auto instance = unique_ptr<LogHandle>(new LogHandle);
		instance->target_ = target;
		return instance;
	}

// OPTIONS
	// Enables or disables passing through of messages of that severity. Everything is enabled by default.
	void Enable(MessageLevel level) {
		if (auto target = target_.lock())
			target->filter().Enable(level);
	}
	void Disable(MessageLevel level) {
		if (auto target = target_.lock())
			target->filter().Disable(level);
	}

// CLOSE
	// Closes this log target, if it is still open.
	void Close();

private:
	// Associated target, non-owning.
	weak_ptr<LogTarget> target_;
};

}  // jiji::core::logging
