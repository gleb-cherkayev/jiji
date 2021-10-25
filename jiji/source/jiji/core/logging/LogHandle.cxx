module jiji:core.logging.LogHandle;
import :prelude;
import :core.logging.Logger;


namespace jiji::core::logging {

// Closes this log target, if it is still open.
void LogHandle::Close() {
	if (auto target = target_.lock())
		theLogger().Close(target);
	target_.reset();
}

}
