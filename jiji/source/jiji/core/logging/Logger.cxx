module jiji:core.logging.Logger;
import :prelude;


namespace jiji::core::logging {

// logging.ixx
void _send_to_logger(Message&& message) {
	theLogger().Consume(std::move(message));
}


// operations.ixx
OperationGuard::OperationGuard() {
	theLogger().begin_operation(*this);
}

OperationGuard::~OperationGuard() {
	theLogger().end_operation(*this);
}

void OperationGuard::operator<<(log_token) {
	theLogger().caption_operation(*this);
}

}  // jiji::core::logging
