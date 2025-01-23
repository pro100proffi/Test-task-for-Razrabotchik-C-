#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <ctime>

// Стандартная тематика
enum class StandardLevel {
    Unknown,
    Info,
    Warning,
    Error
};

// Природная тематика
enum class NatureLevel {
    Unknown,
    Breeze,
    Rain,
    Storm,
    Hurricane
};

// Цветовая тематика
enum class ColorLevel {
    Unknown,
    Green,
    Yellow,
    Orange,
    Red
};

// Общий тип для уровней
enum class Theme {
    Standard,
    Nature,
    Color
};

class Logger {
public:
    Logger(const std::string& filename, Theme theme = Theme::Standard, int defaultLevel = 0);
    ~Logger();

    void setTheme(Theme theme);
    void setDefaultLevel(int level);
    void setLogFile(const std::string& filename);
    void log(const std::string& message, int level = -1); // -1 означает использование уровня по умолчанию

private:
    std::ofstream logFile;
    std::string logFilePath;
    Theme currentTheme;
    int defaultLevel;
    std::mutex logMutex;

    std::string getCurrentTime();
    std::string levelToString(int level);
};


#endif // LOGGER_H