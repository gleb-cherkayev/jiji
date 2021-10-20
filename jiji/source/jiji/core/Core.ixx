export module jiji:core.Core;
import <jiji/_prelude.hxx>;


export namespace jiji::core {

/*
	Main application class.
	Use `jiji::core::Create()` to create and obtain the instance, which should be held until the end of execution.
*/
class Core {
public:
	static unique_ptr<Core> Create() {
		return unique_ptr<Core>(new Core);
	}

// RUN
	// Starts the application.
	// Returns application execution result code (0 for success).
	int Run() {
		return 0;
	}

private:
	Core() = default;

private:
};

}  // jiji::core