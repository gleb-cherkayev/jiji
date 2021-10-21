export module jiji:core.pub;
import :prelude;
import :core.Core;


export namespace jiji::core {

// Triggers application initialisation process.
// Returns the newly created `Core` instance, or nullptr if failed.
unique_ptr<Core> Create(Config const& config) {
	return Core::Create(config);
}

}
