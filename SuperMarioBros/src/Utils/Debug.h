#pragma once

#include <Windows.h>

class Debug
{
public:
	static void Log(const char* format, ...)
	{
        static char s_printf_buf[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(s_printf_buf, sizeof(s_printf_buf), format, args);
        va_end(args);
        OutputDebugStringA(s_printf_buf);
	}
};