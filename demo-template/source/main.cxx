import jiji;


// The entry point.
int main(int argc, const char** argv) {
	jiji::core::Config config;
	auto core = jiji::core::Create(config);
	return core ? core->Run() : -1;
}
