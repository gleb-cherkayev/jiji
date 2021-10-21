export module jiji:core.logging.Logger;
import :prelude;


namespace jiji::core::logging {

class Logger : noncopyable {
public:
	static unique_ptr<Logger> Create() {
		return unique_ptr<Logger>(new Logger);
	}

// LOG
	void WriteLine(string_view) {
	}

private:
	Logger() = default;

private:
};

}