export module jiji:core.Config;
import :prelude;


namespace jiji::core {

constexpr bool default_dev_mode =
#ifdef NDEBUG
false;
#else
true;
#endif

/*
	Provides application initialisation settings.
*/
export struct Config {
	struct {
		bool enable_console_log = false;
		bool enable_debugger_log = false;
	} logging;

public:
	Config(bool is_dev_mode = default_dev_mode) {
		if (!is_dev_mode) return;  // Defaults are OK

		// Dev-mode differences.
		logging.enable_console_log = true;
		logging.enable_debugger_log = true;
	}
};

}  // jiji::core
