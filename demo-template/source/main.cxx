import jiji;


// The entry point.
int main(int argc, const char** argv) {
	auto core = jiji::core::Create();
	return core ? core->Run() : -1;
}
