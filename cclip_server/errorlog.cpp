#include "errorlog.h"

const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

void write_errorlog(std::ofstream& lerr, std::mutex& mtx_errorlog, const std::string& e)
{
	mtx_errorlog.lock();
	lerr << currentDateTime() << " "
		<< e << std::endl;
	mtx_errorlog.unlock();
}

void close_errorlog(std::ofstream& lerr, std::mutex& mtx_errorlog)
{
	mtx_errorlog.lock();
	lerr.close();
	mtx_errorlog.unlock();
}