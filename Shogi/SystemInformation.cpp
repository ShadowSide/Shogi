#include "pch.h"
#include "SystemInformation.h"
#include <sstream>

SystemInformation::SystemInformation(int argc, char * args[])
{
	if (!_executableNameWithoutExtension.empty())
		throw std::logic_error("SystemInformation already initialized");
	InitExecutablePath(argc, args);
	InitNewLine();
}

const std::filesystem::path& SystemInformation::GetExecutablePath()
{
	Check();
	return _executablePath;
}

const std::filesystem::path& SystemInformation::GetExecutableDirectoryPath()
{
	Check();
	return _executableDirectoryPath;
}

const std::string& SystemInformation::GetExecutableName()
{
	Check();
	return _executableName;
}

const std::string& SystemInformation::GetExecutableNameWithoutExtension()
{
	Check();
	return _executableNameWithoutExtension;
}

const std::string& SystemInformation::GetNewLine()
{
	return _newLine;
}

void SystemInformation::Check()
{
	if (_executableNameWithoutExtension.empty())
		throw std::logic_error("SystemInformation not properly initialized");
}

void SystemInformation::InitExecutablePath(int argc, char * args[])
{
	const std::string executablePathInitError = "Wrong initialized executable path for SystemInformation. System or program call is not conformance to application code. ";
	if (argc <= 0)
		throw std::runtime_error(executablePathInitError + "argc <= 0");
	if (!(args[0]))
		throw std::runtime_error(executablePathInitError + "!args[0]");
	std::filesystem::path executablePath = args[0];
	if (executablePath.string().empty())
		throw std::runtime_error(executablePathInitError + "executablePath.string().empty()");
	executablePath = std::filesystem::canonical(executablePath);
	_executablePath = executablePath.string();
	if (_executablePath.string().size() <= MinPathSize)
		throw std::runtime_error(executablePathInitError + "_executablePath.size() <= MinPathSize");
	if (!executablePath.is_absolute())
		throw std::runtime_error(executablePathInitError + "!executablePath.is_absolute()");
	auto executableDirectoryPath = executablePath.parent_path();
	_executableDirectoryPath = executableDirectoryPath.string();
	if (_executableDirectoryPath.string().size() <= MinPathSize)
		throw std::runtime_error(executablePathInitError + "_executableDirectoryPath.size() <= MinPathSize");
	if (!executableDirectoryPath.is_absolute())
		throw std::runtime_error(executablePathInitError + "!executableDirectoryPath.is_absolute()");
	auto filename = executablePath.filename();
	_executableName = filename.string();
	if (_executableName.empty())
		throw std::runtime_error(executablePathInitError + "_executableName.empty()");
	_executableNameWithoutExtension = (filename.has_stem() ? filename.stem() : filename).string();
	if (_executableNameWithoutExtension.empty())
		throw std::runtime_error(executablePathInitError + "_executableNameWithoutExtension.empty()");
}

void SystemInformation::InitNewLine()
{
	std::ostringstream oss;
	oss << std::endl;
	_newLine = oss.str();
}
