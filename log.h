#pragma once
/// <summary>
/// Global for general purpose logging
/// </summary>
struct Log
{
	static void error(const char* format, ...);
	static void error(bool condition, const char* format, ...);
	static void write(const char* format, ...);
};

