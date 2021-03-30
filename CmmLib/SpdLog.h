#pragma once
#include <string>

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT


// #include <spdlog/sinks/basic_file_sink.h>
// #include <spdlog/async.h>
// #include <spdlog/sinks/stdout_color_sinks.h>

//#include <spdlog/spdlog.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
//strrchr:查找字符在指定字符串从右面开始的第一次出现的位置，如果成功，返回该字符以及后面的字符，如果失败，返回NULL
//strcgr:查找字符在指定字符串首次出现的位置
#define __FILENAME__ (strrchr(__FILE__,'\\')?(strrchr(__FILE__,'\\')+1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__,'/')?(strrchr(__FILE__,'/')+1):__FILE__)
#endif //_WIN32

#ifndef SUFFIX
//在错误级别的日志后面追加文件名，函数名，行号
#define SUFFIX(msg) std::string(msg).append("  <")\
                    .append(__FILENAME__).append("> <").append(__FUNCTION__)\
                    .append("> <").append(std::to_string(__LINE__))\
                    .append(">").c_str()
#endif //suffix

/*
日志等级：trace,debug,info,warn,err ,critical
使用方法：包含simlog.h头文件,调用初始化函数,使用LDebug等打印日志信息
例：
CSpdLog::GetInstance().InitLog("scenario_edit", "scenario_edit_log.txt");
int i = 10;
double d_number = 10.01;
LDebug("SimLog::Async message");
LDebug("SimLog::Async message #{0},d_number:{1}", i,d_number);
注：使用{}格式化字符串，里面的数字为占位符
*/

#define LTrace(msg,...)  CSpdLog::GetInstance().GetLogger()->trace(SUFFIX(msg),__VA_ARGS__)
#define LDebug(...)  CSpdLog::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define LInfo(...)  CSpdLog::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LWarn(...) CSpdLog::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LError(msg,...)  CSpdLog::GetInstance().GetLogger()->error(SUFFIX(msg),__VA_ARGS__)
#define LCritical(...)  CSpdLog::GetInstance().GetLogger()->critical(__VA_ARGS__)

//要和spdlog::get_level一致
enum EN_SpdlogLevel
{
	enSpdlogLevel_trace,
	enSpdlogLevel_debug,
	enSpdlogLevel_info,
	enSpdlogLevel_warn,
	enSpdlogLevel_err,
	enSpdlogLevel_critical,
	enSpdlogLevel_off
};

class __declspec(dllexport) CSpdLog
{
public:
	static CSpdLog&GetInstance();
	void InitLog(std::string logger_name, EN_SpdlogLevel log_level = enSpdlogLevel_trace);
	void EndLog();
	void SetLevel(EN_SpdlogLevel level = enSpdlogLevel_trace);
	auto GetLogger()
	{
		return my_logger_;
	}
private:
	CSpdLog();
	~CSpdLog();
	CSpdLog(const CSpdLog &other) = delete;
	CSpdLog& operator=(const CSpdLog &other) = delete;
private:
	std::shared_ptr<spdlog::logger> my_logger_;
};

