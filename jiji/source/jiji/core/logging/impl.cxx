module jiji:core.logging.impl;
import :prelude.no_logging;
import :core.logging.Logger;
import :core.logging.Logger.Operations;


namespace jiji::core::logging {

// LogHandle.ixx

void LogHandle::Close() {
	if (auto target = target_.lock())
		theLogger().Close(target);
	target_.reset();
}


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


// LoggerOperations.ixx

int LoggerOperations::_get_indent() const {
//	return host_.indent_;
	return 0;
}

void LoggerOperations::_indent(int delta) {
	host_.indent(delta);
}

}  // jiji::core::logging
