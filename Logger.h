#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <ctime>

// ����������� ��������
enum class StandardLevel {
    Unknown,
    Info,
    Warning,
    Error
};

// ��������� ��������
enum class NatureLevel {
    Unknown,
    Breeze,
    Rain,
    Storm,
    Hurricane
};

// �������� ��������
enum class ColorLevel {
    Unknown,
    Green,
    Yellow,
    Orange,
    Red
};

// ����� ��� ��� �������
enum class Theme {
    Standard,
    Nature,
    Color
};

class Logger {
public:
    Logger(const std::string& filename, Theme theme = Theme::Standard, int defaultLevel = 0); // 0 = Unknown
    ~Logger();

    void setTheme(Theme theme);
    void setDefaultLevel(int level);
    void log(const std::string& message, int level = -1); // -1 �������� ������������� ������ �� ���������

private:
    std::ofstream logFile;
    Theme currentTheme;
    int defaultLevel; // ������� �������� �� ���������
    std::mutex logMutex;

    std::string getCurrentTime();
    std::string levelToString(int level);
};

#endif // LOGGER_H