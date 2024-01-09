// logger.h

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

enum LogLevel {
    EMERGENCY = 0,
    ALERT = 1,
    CRIT = 2,
    ERROR = 3,
    WARNING = 4,
    NOTICE = 5,
    INFO = 6,
    DEBUG = 7
};

class Logger {
public:
    static void Log(LogLevel level, const std::string& message, int color = -1);
    static void SetLogLevel(LogLevel level);

private:
    static std::string LevelToString(LogLevel level);
    static int GetColor(LogLevel level);
    static void SetColor(int color);
    static void ResetColor();

    static LogLevel currentLogLevel;
};
