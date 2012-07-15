#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "environment.h"
#include "logger.h"
#include "binary_file.h"
#include "console.h"
#include "clock.h"
#include "config_file.h"

namespace System
{

	SingletoneImplementation(Logger);

	string Logger::m_filename = L"punk.log";

	Logger::Logger() : buffer(8192)
	{

#ifdef _DEBUG
		displayToConsole = true;
		displayToFile = true;
#else
		displayToConsole = true;
		displayToFile = true;
#endif

		BinaryFile::Truncate(m_filename);

		WriteDebugMessage(L"Punk Engine Started...");
	}

	Logger::~Logger()
	{
		WriteDebugMessage(L"Punk Engine Stopped...");
		BinaryFile::Append(m_filename, buffer);		
	}

	void Logger::DisplayToConsole(bool value)
	{
		displayToConsole = value;
	}

	void Logger::DisplayToFile(bool value)
	{
		displayToFile = value;
	}

	void Logger::WriteDebugMessage(const string& msg, const string& file, const string& line, const string& function)
	{
		Console::Instance()->SetTextColor(Console::COLOR_LIGHTGRAY);
		if (file.Length())
			Write(Clock::Instance()->ToString() + L" DEBUG => " + msg + L" " + file + L"(" + line + L"): " + function);
		else
			Write(Clock::Instance()->ToString() + L" DEBUG => " + msg);
	}

	void Logger::WriteError(const string& msg, const string& file, const string& line, const string& function)
	{
		Console::Instance()->SetTextColor(Console::COLOR_LIGHTRED);
		if (file.Length())
			Write(Clock::Instance()->ToString() + L" ERROR => " + msg + L" " + file + L"(" + line + L"): " + function);
		else
			Write(Clock::Instance()->ToString() + L" ERROR => " + msg);
	}

	void Logger::WriteWarning(const string& msg, const string& file, const string& line, const string& function)
	{
		Console::Instance()->SetTextColor(Console::COLOR_YELLOW);
		if (file.Length())
			Write(Clock::Instance()->ToString() + L" WARNING => " + msg + L" " + file + L"(" + line + L"): " + function);
		else
			Write(Clock::Instance()->ToString() + L" WARNING => " + msg);
	}

	void Logger::WriteMessage(const string& msg, const string& file, const string& line, const string& function)
	{
		Console::Instance()->SetTextColor(Console::COLOR_LIGHTGREEN);
		if (file.Length())
			Write(Clock::Instance()->ToString() + L" " + msg + L" " + file + L"(" + line + L"): " + function);
		else
			Write(Clock::Instance()->ToString() + L" " + msg);
	}

	void Logger::Write(const string& msg)
	{
		if (buffer.LeftCapacity() < msg.Size())
		{
			BinaryFile::Append(m_filename, buffer);
			buffer.Reset();
		}

		if (displayToConsole)
		{
			Console::Instance()->Print(msg);
			Console::Instance()->Print(L"\n");
		}
		if (displayToFile)
		{
			buffer.WriteString(msg);
			buffer.WriteString(L"\n");
		}
	}
}
