#include "stdafx.h"
#include "SpdLog.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"


CSpdLog::CSpdLog()
{
}


CSpdLog::~CSpdLog()
{
	EndLog();
}

CSpdLog& CSpdLog::GetInstance()
{
	static CSpdLog log;
	return log;
}

void CSpdLog::InitLog(std::string logger_name, EN_SpdlogLevel log_level)
{
	std::string sLogPath;
	sLogPath.append("xlog/");
	sLogPath.append(logger_name);
	sLogPath.append(".log");
	//设置日志等级
	//my_logger_ = spdlog::basic_logger_mt<spdlog::async_factory >(logger_name, file_name);
	my_logger_ = spdlog::basic_logger_mt<spdlog::synchronous_factory >(sLogPath, sLogPath);
	my_logger_->set_level(static_cast<spdlog::level::level_enum>(log_level));
	my_logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P/%t] [%l] %v");
	//当遇到错误级别以上的立刻刷新到日志
	my_logger_->flush_on(spdlog::level::trace);
	//每三秒刷新一次
	//spdlog::flush_every(std::chrono::seconds(3));

}

void CSpdLog::EndLog()
{
	spdlog::shutdown();
}

void CSpdLog::SetLevel(EN_SpdlogLevel level)
{
	my_logger_->set_level(static_cast<spdlog::level::level_enum>(level));
}
