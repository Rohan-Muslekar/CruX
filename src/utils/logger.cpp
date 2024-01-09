// logger.cpp

#include "server.h"

LogLevel Logger::currentLogLevel = INFO;

void Logger::Log(LogLevel level, const std::string& message, int color) {
    if (color >= 0) {
        SetColor(color);
    } else if (GetColor(level) >= 0) {
        SetColor(GetColor(level));
    }
    std::cout << "[" << LevelToString(level) << "] " << getTimeStr() << message << std::endl;

    if (color >= 0 || GetColor(level) >= 0) {
        ResetColor();
    }
}

void Logger::SetLogLevel(LogLevel level) {
    currentLogLevel = level;
}

std::string Logger::LevelToString(LogLevel level) {
    switch (level) {
    case EMERGENCY: return "EMERGENCY";
    case ALERT: return "ALERT";
    case CRIT: return "CRIT";
    case ERROR: return "ERROR";
    case WARNING: return "WARNING";
    case NOTICE: return "NOTICE";
    case INFO: return "INFO";
    case DEBUG: return "DEBUG";
    default: return "UNKNOWN";
    }
}

int Logger::GetColor(LogLevel level) {
    switch (level) {
    case EMERGENCY: return 0;
    case ALERT: return 1;
    case CRIT: return 2;
    case ERROR: return 3;
    case WARNING: return 4;
    case NOTICE: return 5;
    case INFO: return 6;
    case DEBUG: return 7;
    default: return 8;
    }
}

void Logger::SetColor(int color) {
    const std::string colorCodes[] = {
        "\x1B[31m", "\x1B[91m", "\x1B[35m", "\x1B[95m",
        "\x1B[33m", "\x1B[93m", "\x1B[32m", "\x1B[92m", "\x1B[97m"
    };

    if (color >= 0 && color < 8) {
        std::cout << colorCodes[color];
    }
}

void Logger::ResetColor() {
    std::cout << "\x1B[0m";
}
