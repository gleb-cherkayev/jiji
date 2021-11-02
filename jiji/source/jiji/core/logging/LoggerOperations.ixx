export module jiji:core.logging.Logger.Operations;
import :prelude;


namespace jiji::core::logging {
class Logger;

/*
	Subsystem for Logger class implementing operations functionality.
*/
class LoggerOperations {
private:
	LoggerOperations(Logger& host) : host_(host) {}

public:
	static unique_ptr<LoggerOperations> Create(Logger& host) {
		return unique_ptr<LoggerOperations>(new LoggerOperations(host));
	}

	bool InProgress() const {
		return !pending_.empty();
	}

	void Log(Message&& message) {
		//auto& op = pending_.back();

		//if (!op.captioned) {
		//	// Message means non-trivial, so actualised all outer
		//	this->_actualise_outer();

		//	// If it's the first message, it might yet become a header.
		//	// Otherwise, time to actualise it.
		//	if (op.start < (int)messages_.size())
		//		this->_captionise(op);
		//}

		//if (message.level == MessageLevel::Error || message.level == MessageLevel::Warning) {
		//	if (!op.captioned)
		//		this->_captionise(op);  // Cannot be a header.

		//	// Also mark as alerted.
		//	pending_.back().alerted = true;
		//}

		//messages_.push_back(std::move(message));
	}

	void Push(OperationGuard const&) {
		// Generate a caption for the immediate prior scope if necessary.
		if (!pending_.empty()) {
			auto& op = pending_.back();
			if (!op.captioned)
				this->_captionise(op);
		}

		// Add new scope.
		int start = (int)messages_.size();
		pending_.push_back({.start = start, .indent = this->_get_indent()});
		this->_indent(+1);
	}

	int _get_indent() const;
	void _indent(int);

	void Consummate(OperationGuard const&) {
		//// Since there was a log message, all outer levels are already actualised.
		//// The current one might be as well.

		//// Assuming we are not trying to break it, i.e. logging token is not used twice etc.
		//// Therefore, there *is* a free message, not used as a header in an outer operation.
		//assert(!pending_.empty());
		//assert(!messages_.empty());

		//// Check if already actualised.
		//auto& op = pending_.back();
		//if (op.captioned) return;

		//// Last message is a header, can't be warning or error.
		//auto& messageLast = messages_.back();
		//assert(op.start == (int)messages_.size() - 1);
		//assert(messageLast.level != MessageLevel::Error || messageLast.level != MessageLevel::Warning);
		//messageLast.indent = op.indent;
		//messageLast.suffixed = true;
		//op.captioned = true;
	}

	void Pop(OperationGuard const&) {
		//assert(!pending_.empty());

		//auto& op = pending_.back();
		//if (!op.captioned) {
		//	if (op.start < (int)messages_.size())
		//		this->_captionise(op);
		//	else {
		//		// trivial: no messages, no header, no alert
		//		host_.indent(-1);
		//		pending_.pop_back();
		//		return;
		//	}
		//}

		//// Set the result to the header.
		//int indexHeader = op.start;
		//messages_[indexHeader].result = guard.result();
		//if (guard.result() != true)
		//	op.alerted = true;

		//if (guard.is_quiet() && guard.result() == true) {
		//	// Decides whether the message should be dropped in quiet mode.
		//	auto shouldSuppress = [alerted = op.alerted](Message& message)
		//	{
		//		// If not alerted, drop everything.
		//		if (!alerted) return true;
		//		// If alerted, keep headers and warnings/errors.
		//		return !(message.suffixed || message.level == MessageLevel::Error || message.level == MessageLevel::Warning);
		//	};

		//	messages_.erase(
		//		std::remove_if(messages_.begin() + indexHeader, messages_.end(), shouldSuppress)
		//		, messages_.end());
		//}

		//// ... and pop
		//bool alerted = pending_.back().alerted;
		//host_.indent(-1);
		//pending_.pop_back();
		//if (alerted && !pending_.empty())
		//	pending_.back().alerted = true;

		//if (pending_.empty()) {
		//	auto flush_message = [](auto& log, auto const& line) {
		//		if (!log->filter().Accepts(line.source, line.level)) return;
		//		if (line.suffixed) {
		//			log->WritePrefix(line);
		//			if (!line.result)
		//				log->WriteSuffix(" <Unknown>\n", MessageLevel::Warning);
		//			else if (*line.result)
		//				log->WriteSuffix(" OK\n", MessageLevel::Success);
		//			else
		//				log->WriteSuffix(" FAILED!\n", MessageLevel::Error);
		//		}
		//		else
		//			log->WriteLine(line);
		//	};

		//	// Flush.
		//	assert(indexHeader == 0);
		//	for (auto p = messages_.begin() + indexHeader; p != messages_.end(); ++p)
		//		for (auto& log : host_.logs_)
		//			flush_message(log, *p);
		//	messages_.erase(messages_.begin() + indexHeader, messages_.end());
		//}
	}

private:
	
	// Ensures that missing headers are created all way up, but not including the current.
	void _actualise_outer() {
		//assert(!pending_.empty());

		//int indexLast = pending_.size() - 2;
		//if (indexLast < 0) return;  // too deep

		//if (pending_[indexLast].captioned) return;

		//// Find the earliest without the header.
		//auto pe = pending_.begin() + indexLast;
		//auto p = pe;
		//for (; p != pending_.begin() && !p->captioned; --p);
		//++pe;

		//for (; p != pe; ++p)
		//	this->_captionise(*p);
	}
	// Adds a default caption for this operation.
	struct PendingOperation;
	void _captionise(PendingOperation& op) {
		//assert(!op.captioned);

		//Message message
		//{
		//	.indent = op.indent,  // Use stored indent at the beginning of operation.
		//	.source = MessageSource::System,
		//	.level = MessageLevel::Log,
		//	.timestamp = host_.get_current_time(),
		//	.body = "<Unknown operation>...",
		//	.suffixed = true
		//};
		//messages_.insert(messages_.begin() + op.start, std::move(message));
		//op.captioned = true;
	}

private:
	// Owner instance.
	Logger& host_;

	// Stack of pending messages.
	std::vector<Message> messages_;

	struct PendingOperation {
		int start = -1;
		int indent = 0;
		bool alerted = false;
		bool captioned = false;
	};
	// Stack of pending operations.
	std::vector<PendingOperation> pending_;
};

}  // jiji::core::logging
