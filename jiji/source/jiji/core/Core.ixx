export module jiji:core.Core;
import :prelude;
import :core.EngineCore;


export namespace jiji::core {

/*
	Main application class.
	Use `jiji::core::Create()` to create and obtain the instance, which should be held until the end of execution.
*/
class Core {
public:
	static unique_ptr<Core> Create() {
		auto instance = unique_ptr<Core>(new Core);
		if (!instance->_init()) return nullptr;
		return instance;
	}

// RUN
	// Starts the application.
	// Returns application execution result code (0 for success).
	int Run() {
		return 0;
	}

private:
	Core() = default;

	// Performs actual initialisation.
	// Returns true if successful and the instance is useable, or false otherwise.
	bool _init() {
		engine_ = EngineCore::Create();
		if (!engine_) return false;

		return true;
	}

private:
	unique_ptr<EngineCore> engine_;
};

}  // jiji::core
