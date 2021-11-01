export module jiji:core.logging.operations;
import :prelude.no_logging;
import :core.logging.routines;


namespace jiji::core::logging {

/*
	Helper for logging operation status and progress.
	Can be nested.
*/
class OperationGuard : noncopyable {
public:
	OperationGuard();
	// NOTE: Non-virtual, but that's fine.
	~OperationGuard();

	// Chaining the header.
	// After declaration, use this to set the header:
	// ```
	//	OperationGuard operation;
	//	operation << log_loading("Loading...");
	// ```
	// If skipped, default header will be created by the next message coming to the logger.
	void operator<<(log_token);

// RESULT:
	// Sets result as failed. Returns false.
	bool Fail() { status_ = false; return false; }
	// Sets result as success. Returns true.
	bool Succeed() { status_ = true; return true; }
	// Set result to the given boolean
	bool SetResult(bool status) { status_ = status; return status; }
	// Returns the result. May be not set.
	optional<bool> result() const { return status_; }

	// Denotes whether to drop messages when successful.
	// See QuietOperationGuard.
	bool is_quiet() const { return quiet_; }

protected:
	optional<bool> status_;
	bool quiet_ = false;
};


/*
	Same as OperationGuard, but silently drops messages in case of eventual success.
	NOTE: Errors and warnings are always logged.
*/
class QuietOperationGuard : public OperationGuard {
public:
	QuietOperationGuard() {
		quiet_ = true;
	}
};
static_assert(sizeof(QuietOperationGuard) == sizeof(OperationGuard));

}  // jiji::core::logging
