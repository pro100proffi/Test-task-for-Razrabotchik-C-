#include "Logger.h"
#include <iostream>
#include <thread>
#include <string>
#include <cstdlib> // для getenv

// Функция для получения пути к папке "Документы"
std::string getDocumentsPath() {
    const char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        std::cerr << "Error: HOME environment variable not found.\n";
        return "";
    }
    return std::string(homeDir) + "/Documents/log.txt";
}

void printMenu() {
    std::cout << "\n=== Logger Application ===\n"
        << "1. Choose logging theme\n"
        << "2. Log a message\n"
        << "3. Change default log level\n"
        << "4. Choose log file\n"
        << "5. Exit\n"
        << "Enter your choice: ";
}

void chooseTheme(Logger& logger) {
    int themeChoice;
    std::cout << "\nChoose a logging theme:\n"
        << "1. Standard (Info, Warning, Error)\n"
        << "2. Nature (Breeze, Rain, Storm, Hurricane)\n"
        << "3. Color (Green, Yellow, Orange, Red)\n"
        << "Enter your choice (1, 2, or 3): ";
    std::cin >> themeChoice;

    switch (themeChoice) {
    case 1: logger.setTheme(Theme::Standard); break;
    case 2: logger.setTheme(Theme::Nature); break;
    case 3: logger.setTheme(Theme::Color); break;
    default:
        std::cerr << "Invalid choice. Using Standard theme.\n";
        logger.setTheme(Theme::Standard);
        break;
    }
}

void logMessage(Logger& logger) {
    std::string message;
    int level;

    std::cout << "\nEnter your message: ";
    std::cin.ignore(); // Игнорируем предыдущий ввод
    std::getline(std::cin, message);

    std::cout << "Enter log level (or -1 for default): ";
    std::cin >> level;

    logger.log(message, level);
    std::cout << "Message logged successfully.\n";
}

void changeDefaultLevel(Logger& logger) {
    int level;
    std::cout << "\nEnter new default log level: ";
    std::cin >> level;

    logger.setDefaultLevel(level);
    std::cout << "Default log level changed successfully.\n";
}

void chooseLogFile(Logger& logger) {
    std::string logFilePath;
    std::cout << "\nEnter the path to the log file: ";
    std::cin >> logFilePath;

    logger.setLogFile(logFilePath);
    std::cout << "Log file set to: " << logFilePath << "\n";
}

int main() {
    // Получаем путь к папке "Документы" по умолчанию
    std::string logFilePath = getDocumentsPath();
    if (logFilePath.empty()) {
        std::cerr << "Failed to determine Documents folder path. Using current directory.\n";
        logFilePath = "log.txt";
    }

    Logger logger(logFilePath, Theme::Standard);

    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            chooseTheme(logger);
            break;
        case 2:
            logMessage(logger);
            break;
        case 3:
            changeDefaultLevel(logger);
            break;
        case 4:
            chooseLogFile(logger);
            break;
        case 5:
            std::cout << "Exiting application.\n";
            return 0;
        default:
            std::cerr << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}