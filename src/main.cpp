
#include "Engine.h"
#include "Log.h"
#include "tests.h"

int main(int argc, char* argv[])
{
	spe::Log::init("shinypanda.log", true);
	spe::startTests();

	spe::Engine engine(argc, argv);

    int exitCode = engine.run();

	spe::Log::close();

	return exitCode;
}
