#include <windows.h>
#include "Debug.h"

void Debug::Log(int value, bool isLineFeed)
{
	char str[256];
	sprintf_s(str, "%d", value);
	Debug::Log(str, isLineFeed);
}

void Debug::Log(float value, bool isLineFeed)
{
	char str[256];
	sprintf_s(str, "%f", value);
	Debug::Log(str, isLineFeed);
}

void Debug::Log(bool flag, bool isLineFeed)
{
	const char* str=(flag ? "true" : "false");
	Debug::Log(std::string(str), isLineFeed);
}

void Debug::Log(std::string value, bool isLineFeed)
{
	if (isLineFeed)	value += "\n";
	OutputDebugString(value.c_str());
}
