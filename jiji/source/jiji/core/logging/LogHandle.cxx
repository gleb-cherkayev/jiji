module jiji:core.logging.LogHandle;
import :prelude;
//import :core.logging.LogHandle;
import :core.logging.Logger;


namespace jiji::core::logging {

void LogHandle::Close() {
	if (auto target = target_.lock())
		theLogger().Close(target);
	target_.reset();
}

}
