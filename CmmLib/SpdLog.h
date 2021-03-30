#pragma once
#include <string>

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT


// #include <spdlog/sinks/basic_file_sink.h>
// #include <spdlog/async.h>
// #include <spdlog/sinks/stdout_color_sinks.h>

//#include <spdlog/spdlog.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
//strrchr:�����ַ���ָ���ַ��������濪ʼ�ĵ�һ�γ��ֵ�λ�ã�����ɹ������ظ��ַ��Լ�������ַ������ʧ�ܣ�����NULL
//strcgr:�����ַ���ָ���ַ����״γ��ֵ�λ��
#define __FILENAME__ (strrchr(__FILE__,'\\')?(strrchr(__FILE__,'\\')+1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__,'/')?(strrchr(__FILE__,'/')+1):__FILE__)
#endif //_WIN32

#ifndef SUFFIX
//�ڴ��󼶱����־����׷���ļ��������������к�
#define SUFFIX(msg) std::string(msg).append("  <")\
                    .append(__FILENAME__).append("> <").append(__FUNCTION__)\
                    .append("> <").append(std::to_string(__LINE__))\
                    .append(">").c_str()
#endif //suffix

/*
��־�ȼ���trace,debug,info,warn,err ,critical
ʹ�÷���������simlog.hͷ�ļ�,���ó�ʼ������,ʹ��LDebug�ȴ�ӡ��־��Ϣ
����
CSpdLog::GetInstance().InitLog("scenario_edit", "scenario_edit_log.txt");
int i = 10;
double d_number = 10.01;
LDebug("SimLog::Async message");
LDebug("SimLog::Async message #{0},d_number:{1}", i,d_number);
ע��ʹ��{}��ʽ���ַ��������������Ϊռλ��
*/

#define LTrace(msg,...)  CSpdLog::GetInstance().GetLogger()->trace(SUFFIX(msg),__VA_ARGS__)
#define LDebug(...)  CSpdLog::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define LInfo(...)  CSpdLog::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LWarn(...) CSpdLog::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LError(msg,...)  CSpdLog::GetInstance().GetLogger()->error(SUFFIX(msg),__VA_ARGS__)
#define LCritical(...)  CSpdLog::GetInstance().GetLogger()->critical(__VA_ARGS__)

//Ҫ��spdlog::get_levelһ��
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

