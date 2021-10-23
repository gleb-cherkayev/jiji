export module jiji:core.logging.sinks.DebuggerLogSink;
import :prelude;
import :core.logging.sinks.LogSink;
import :core.logging.LogTarget;
import :env.windows;


namespace jiji::core::logging {

/*
	Under Windows OS, provides log service through OutputDebugString() WinAPI call.
*/
class DebuggerLogSink : public LogSink {
public:
	static shared_ptr<LogTarget> OpenLog() {
		auto instance = unique_ptr<DebuggerLogSink>(new DebuggerLogSink);
		return LogTarget::Open(std::move(instance));
	}

	string_view name() const override { return "Debugger"; };

//	void Write(Message const&, bool eol, LogTarget::Appearance const&) override;
	void Write(string_view message/*, MessageLevel*/) override {
		::OutputDebugStringA(message.data());
	}

private:
	DebuggerLogSink() = default;
};

}  // jiji::core::logging

#if 0
void lili::tool::log::DebuggerLogSink::Write(Message const& message, bool eol, LogTarget::Appearance const& appearance) {
	static_assert(sizeof(wchar_t) == sizeof(char16_t));
	::OutputDebugString((wchar_t*)default_format(message, eol, appearance).to_utf16().c_str());
}

void lili::tool::log::DebuggerLogSink::Write(string_view message, MessageLevel) {
	std::u16string message_u16;
	unicode::convert_utf8to16_unchecked(message.begin(), message.end(), std::back_inserter(message_u16));
	::OutputDebugString((wchar_t*)message_u16.c_str());
}
#endif