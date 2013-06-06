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

	Log(LOG_TYPE::DEBUG) << "DEBU GUB UBGEUB EBUE 1" << std::endl;
	Log(LOG_TYPE::WARNING) << "DEBU GUB UBGEUB EBUE 2" << std::endl;
	Log(LOG_TYPE::ERROR) << "DEBU GUB UBGEUB EBUE 3";

	Log(LOG_TYPE::ERROR) << "ERREEUR AHAHHA";
	Log(LOG_TYPE::ERROR) << "ERREEUR2 AHAHHA";
	Log(LOG_TYPE::WARNING) << "ERREEUR2 AHAHHA";

	Log(LOG_TYPE::ERROR) << "test1" << std::endl; //multi lines
	Log() << "test2" << std::endl;
	Log() << "test3";

	Log::close();
}