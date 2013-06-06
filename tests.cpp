#include "Log.h"

using namespace spe;

void test_log()
{
	Log::init("test.log", true);

	Log() << "int " << 23 << " test";
	Log() << "long " << 1e32 << " test";
	Log() << "float " << 3.3f << " test";
	Log() << "double " << 3.3123312 << " test";
	Log() << "char " << 'g' << " test";
	Log() << "str " << " balbla" << " test";

	Log() << "test " << 32 << " after"; //single line

	Log() << "test1" << std::endl; //multi lines
	Log() << "test2" << std::endl;
	Log() << "test3";

	Log(DEBUG) << "DEBU GUB UBGEUB EBUE 1" << std::endl;
	Log(WARNING) << "DEBU GUB UBGEUB EBUE 2" << std::endl;
	Log(ERROR) << "DEBU GUB UBGEUB EBUE 3";

	Log(ERROR) << "ERREEUR AHAHHA";
	Log(ERROR) << "ERREEUR2 AHAHHA";
	Log(WARNING) << "ERREEUR2 AHAHHA";

	Log(ERROR) << "test1" << std::endl; //multi lines
	Log() << "test2" << std::endl;
	Log() << "test3";

	Log::close();
}
