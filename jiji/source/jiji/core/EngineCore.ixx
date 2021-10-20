export module jiji:core.EngineCore;
import <jiji/_prelude.hxx>;


namespace jiji::core {

/*
	Initialises and holds low-level subsystems.
	In turn, is owned by `Core`.
*/
class EngineCore {
public:
	static unique_ptr<EngineCore> Create() {
		return unique_ptr<EngineCore>(new EngineCore);
	}

private:
	EngineCore() = default;

private:
};

}  // jiji::core
