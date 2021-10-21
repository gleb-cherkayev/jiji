export module jiji:core.Core;
import :prelude;
import :core.EngineCore;


namespace jiji::core {

/*
	Main application class.
	Use `jiji::core::Create()` to create and obtain the instance, which should be held until the end of execution.
*/
export class Core : noncopyable {
public:
	static unique_ptr<Core> Create(Config const& config) {
		auto instance = unique_ptr<Core>(new Core);
		if (!instance->_init(config)) return nullptr;
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
	bool _init(Config const& config) {
		engine_ = EngineCore::Create(config);
		if (!engine_) return false;

		return true;
	}

private:
	unique_ptr<EngineCore> engine_;
};

}  // jiji::core
