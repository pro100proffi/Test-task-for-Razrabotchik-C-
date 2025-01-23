#include "Logger.h"
#include <iostream>

Logger::Logger(const std::string& filename, Theme theme, int defaultLevel)
    : logFilePath(filename), currentTheme(theme), defaultLevel(defaultLevel) {
    logFile.open(logFilePath, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Could not open log file: " + logFilePath);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setTheme(Theme theme) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentTheme = theme;
}

void Logger::setDefaultLevel(int level) {
    std::lock_guard<std::mutex> lock(logMutex);
    defaultLevel = level;
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFilePath = filename;
    logFile.open(logFilePath, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Could not open or create log file: " + logFilePath);
    }

    std::cout << "Log file set to: " << logFilePath << "\n";
}

void Logger::log(const std::string& message, int level) {
    std::lock_guard<std::mutex> lock(logMutex);

    // Åñëè óðîâåíü íå óêàçàí, èñïîëüçóåì óðîâåíü ïî óìîë÷àíèþ
    int effectiveLevel = (level == -1) ? defaultLevel : level;

    logFile << "[" << getCurrentTime() << "] "
        << "[" << levelToString(effectiveLevel) << "] "
        << message << std::endl;
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;

    // Èñïîëüçóåì localtime_r äëÿ Linux
    localtime_r(&now_time, &now_tm);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
    return std::string(buffer);
}

std::string Logger::levelToString(int level) {
    switch (currentTheme) {
    case Theme::Standard:
        switch (static_cast<StandardLevel>(level)) {
        case StandardLevel::Unknown: return "UNKNOWN";
        case StandardLevel::Info: return "INFO";
        case StandardLevel::Warning: return "WARNING";
        case StandardLevel::Error: return "ERROR";
        default: return "UNKNOWN";
        }
    case Theme::Nature:
        switch (static_cast<NatureLevel>(level)) {
        case NatureLevel::Unknown: return "UNKNOWN";
        case NatureLevel::Breeze: return "BREEZE";
        case NatureLevel::Rain: return "RAIN";
        case NatureLevel::Storm: return "STORM";
        case NatureLevel::Hurricane: return "HURRICANE";
        default: return "UNKNOWN";
        }
    case Theme::Color:
        switch (static_cast<ColorLevel>(level)) {
        case ColorLevel::Unknown: return "UNKNOWN";
        case ColorLevel::Green: return "GREEN";
        case ColorLevel::Yellow: return "YELLOW";
        case ColorLevel::Orange: return "ORANGE";
        case ColorLevel::Red: return "RED";
        default: return "UNKNOWN";
        }
    default:
        return "UNKNOWN";
    }
}
