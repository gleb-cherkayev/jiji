export module jiji:core.pub;
import <jiji/_prelude.hxx>;
import :core.Core;


export namespace jiji::core {

// Triggers application initialisation process.
// Returns the newly created `Core` instance, or nullptr if failed.
unique_ptr<Core> Create() {
	return Core::Create();
}

}
