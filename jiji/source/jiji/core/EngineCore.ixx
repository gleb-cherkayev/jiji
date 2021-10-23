export module jiji:core.EngineCore;
import :prelude;
import :core.Config;
import :core.logging.Logger;


namespace jiji::core {

/*
	Initialises and holds low-level subsystems.
	In turn, is owned by `Core`.
*/
class EngineCore : noncopyable {
private:
	EngineCore() {
		JIJI_COMMENT_HERE;
	}

	// Performs actual initialisation of all low-level subsystems.
	// Returns true if successful, and false otherwise.
	bool _init(Config const& config) {
		if (config.logging.enable_debugger_log)
			theLogger().OpenDebuggerLog();

		theLogger().WriteLine("TEST");

		return true;
	}

public:
	~EngineCore() {
		JIJI_COMMENT_HERE;
	}

	static unique_ptr<EngineCore> Create(Config const& config) {
		auto instance = unique_ptr<EngineCore>(new EngineCore);
		if (!instance->_init(config)) return nullptr;
		return instance;
	}

private:

private:
	
};

}  // jiji::core
