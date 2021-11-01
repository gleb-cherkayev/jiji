export module jiji:prelude;
export import :prelude.no_logging;
export import :core.logging.routines;
import :core.logging.operations;


namespace jiji {
using OperationGuard = jiji::core::logging::OperationGuard;
using QuietOperationGuard = jiji::core::logging::QuietOperationGuard;
}