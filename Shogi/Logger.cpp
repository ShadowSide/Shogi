#include "pch.h"
#include "Locator.h"
#include "Logger.h"
using namespace std::string_literals;

void Logger::Init()
{
	if (_file.is_open())
		throw std::logic_error("ALready initialized Logger");
	_file = std::fstream(Locator::Resolve<ISystemInformation>()->GetExecutableDirectoryPath() / (Locator::Resolve<ISystemInformation>()->GetExecutableNameWithoutExtension() + ".log"), std::fstream::out | std::fstream::trunc);
	WriteInfo("Logger::Init");
}

void Logger::AttachLogFromSdl2Log()
{
	SDL_LogSetOutputFunction(WriteLogSdl2, nullptr);
}

void Logger::WriteTrace(std::string_view msg)
{
	WriteLog(GetInformationAndFormatLog("Trace", msg));
}

void Logger::WriteInfo(std::string_view msg)
{
	WriteLog(GetInformationAndFormatLog("Info", msg));
}

void Logger::WriteWarn(std::string_view msg)
{
	WriteLog(GetInformationAndFormatLog("Warn", msg));
}

void Logger::WriteError(std::string_view msg)
{
	WriteLog(GetInformationAndFormatLog("Warn", msg));
}

void Logger::WriteTrace(const std::exception& msg)
{
	WriteLog(GetInformationAndFormatLog("Trace", "|Exception|"s + typeid(msg).name() + ": " + msg.what()));
}

void Logger::WriteInfo(const std::exception& msg)
{
	WriteLog(GetInformationAndFormatLog("Info", "|Exception|"s + typeid(msg).name() + ": " + msg.what()));
}

void Logger::WriteWarn(const std::exception& msg)
{
	WriteLog(GetInformationAndFormatLog("Warn", "|Exception|"s + typeid(msg).name() + ": " + msg.what()));
}

void Logger::WriteError(const std::exception& msg)
{
	WriteLog(GetInformationAndFormatLog("Error", "|Exception|"s + typeid(msg).name() + ": " + msg.what()));
}

void Logger::Close()
{
	_file.flush();
	_file.close();
}

void Logger::WriteLog(std::string_view msg)
{
	const static auto newLine = Locator::Resolve<ISystemInformation>()->GetNewLine();
	_file << msg << newLine << std::flush;
}

std::string Logger::GetInformationAndFormatLog(std::string_view categoryName, std::string_view msg)
{
	return GetCommonInformationAndFormatLog("|Project|"s + std::string(categoryName) + "|"s + std::string(msg));
}

std::string Logger::GetInformationAndFormatLog(int category, SDL_LogPriority priority, std::string_view msg)
{
	return GetCommonInformationAndFormatLog("|SDL2|"s + GetSdl2CategoryName(category) + "|"s + GetSdl2PriorityName(priority) + "|"s + std::string(msg));
}

std::string Logger::GetCommonInformationAndFormatLog(std::string_view msg)
{
	return std::string(msg) + "% TODO: implement |datetime|, |tid in Logger";
}

void Logger::WriteLogSdl2(void * userdata, int category, SDL_LogPriority priority, const char * message)
{
	WriteLog(GetInformationAndFormatLog(category, priority, message));
}

std::string Logger::GetSdl2CategoryName(int category)
{
	switch (category)
	{
	case SDL_LOG_PRIORITY_VERBOSE:
		return "VERBOSE";
	case SDL_LOG_PRIORITY_DEBUG:
		return "DEBUG";
	case SDL_LOG_PRIORITY_INFO:
		return "INFO";
	case SDL_LOG_PRIORITY_WARN:
		return "WARN";
	case SDL_LOG_PRIORITY_ERROR:
		return "ERROR";
	case SDL_LOG_PRIORITY_CRITICAL:
		return "CRITICAL";
	default:
		return "UnknownCategory";
	}
}

std::string Logger::GetSdl2PriorityName(SDL_LogPriority priority)
{
	switch (priority)
	{
	case SDL_LOG_CATEGORY_APPLICATION:
		return "APPLICATION";
	case SDL_LOG_CATEGORY_ERROR:
		return "ERROR";
	case SDL_LOG_CATEGORY_ASSERT:
		return "ASSERT";
	case SDL_LOG_CATEGORY_SYSTEM:
		return "SYSTEM";
	case SDL_LOG_CATEGORY_AUDIO:
		return "AUDIO";
	case SDL_LOG_CATEGORY_VIDEO:
		return "VIDEO";
	case SDL_LOG_CATEGORY_RENDER:
		return "RENDER";
	case SDL_LOG_CATEGORY_INPUT:
		return "INPUT";
	case SDL_LOG_CATEGORY_TEST:
		return "TEST";
	case SDL_LOG_CATEGORY_RESERVED1:
		return "RESERVED1";
	case SDL_LOG_CATEGORY_RESERVED2:
		return "RESERVED2";
	case SDL_LOG_CATEGORY_RESERVED3:
		return "RESERVED3";
	case SDL_LOG_CATEGORY_RESERVED4:
		return "RESERVED4";
	case SDL_LOG_CATEGORY_RESERVED5:
		return "RESERVED5";
	case SDL_LOG_CATEGORY_RESERVED6:
		return "RESERVED6";
	case SDL_LOG_CATEGORY_RESERVED7:
		return "RESERVED7";
	case SDL_LOG_CATEGORY_RESERVED8:
		return "RESERVED8";
	case SDL_LOG_CATEGORY_RESERVED9:
		return "RESERVED9";
	case SDL_LOG_CATEGORY_RESERVED10:
		return "RESERVED10";
	case SDL_LOG_CATEGORY_CUSTOM:
		return "CUSTOM";
	default:
		return "UnknownPriority";
	}
}

void Logger::Check()
{
	if (!_file.is_open())
		throw std::logic_error("Not initalized or closed Logger");
}
