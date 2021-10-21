export module jiji:core.EngineCore;
import :prelude;
import :core.logging.Logger;


namespace jiji::core {

/*
	Initialises and holds low-level subsystems.
	In turn, is owned by `Core`.
*/
class EngineCore : noncopyable {
public:
	static unique_ptr<EngineCore> Create() {
		auto instance = unique_ptr<EngineCore>(new EngineCore);
		if (!instance->_init()) return nullptr;
		return instance;
	}

private:
	EngineCore() = default;

	bool _init() {
		logger_ = logging::Logger::Create();
		if (!logger_) return false;

		return true;
	}

private:
	unique_ptr<logging::Logger> logger_;
};

}  // jiji::core
