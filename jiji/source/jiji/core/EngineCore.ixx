export module jiji:core.EngineCore;
import :prelude;
import :core.Config;


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

	bool _init(Config const& config) {

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
