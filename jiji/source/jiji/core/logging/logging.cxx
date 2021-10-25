module jiji:core.logging.routines;
import :prelude;
import :core.logging.Logger;


namespace jiji::core::logging {

void _send_to_logger(Message&& message) {
	theLogger().Consume(std::move(message));
}

}  // jiji::core::logging
