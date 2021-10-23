module jiji:core.logging.logging;
//import :prelude;
import :core.logging.Logger;
import :core.logging.Message;


namespace jiji::core::logging {

void pass_to_logger(Message const& message) {
	theLogger().WriteLine(message.text);
}

}