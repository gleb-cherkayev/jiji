export module jiji:core.Core;
import :prelude;
import :core.EngineCore;
import :core.logging.Logger;


namespace jiji::core {

/*
	Main application class.
	Use `jiji::core::Create()` to create and obtain the instance, which should be held until the end of execution.
*/
export class Core : noncopyable {
private:	
	Core() {
		JIJI_COMMENT_HERE;  // Safe, as a logger already exists.
		assert(!instance_);
		instance_ = this;
	}

	// Performs actual initialisation.
	// Returns true if successful and the instance is useable, or false otherwise.
	bool _init(Config const& config) {
		// logger_ is already set. Targets are set-up by EngineCore.

		engine_ = EngineCore::Create(config);
		if (!engine_) return false;

		return true;
	}

public:
	~Core() {
		JIJI_COMMENT_HERE;
		assert(instance_ == this);
		instance_ = nullptr;
		// And the logger dies here, the last of members.
	}

	static unique_ptr<Core> Create(Config const& config) {
		if (instance_) {
			JIJI_ERROR("Core already created.");
			return nullptr;
		}
		
		// Start with a logger.
		auto logger = logging::Logger::Create();
		if (!logger) return nullptr;

		auto instance = unique_ptr<Core>(new Core);
		instance->logger_ = std::move(logger);

		if (!instance->_init(config)) return nullptr;
		log_double_separator();
		return instance;
	}

// RUN
	// Starts the application.
	// Returns application execution result code (0 for success).
	int Run() {
		return 0;
	}

private:


private:
	// Logger holder.
	// The first field, so that it is destroyed the last.
	unique_ptr<logging::Logger> logger_;
	// Low-level systems holder.
	unique_ptr<EngineCore> engine_;

	// Singleton instance.
	static Core* instance_;
	friend Core& theCore() {
		assert(instance_);
		return *instance_;
	}
};

Core* Core::instance_ = nullptr;

}  // jiji::core
