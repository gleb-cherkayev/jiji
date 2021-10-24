module jiji:core.logging.routines;
import :prelude;
import :core.logging.Logger;


namespace jiji::core::logging {

void send_to_logger(Message const& message) {
	theLogger().WriteLine(message);
}

}  // jiji::core::logging
