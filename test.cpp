#include "Logger.h"
#include <cassert>

void testLogger() {
    Logger logger("test_log.txt", Theme::Standard);

    // Проверка стандартной тематики
    logger.log("Test info message.", static_cast<int>(StandardLevel::Info));
    logger.log("Test warning message.", static_cast<int>(StandardLevel::Warning));
    logger.log("Test error message.", static_cast<int>(StandardLevel::Error));

    // Проверка уровня по умолчанию (Unknown)
    logger.log("Test default level message.");

    // Проверка изменения тематики
    logger.setTheme(Theme::Nature);
    logger.log("Test breeze message.", static_cast<int>(NatureLevel::Breeze));

    // Проверка изменения уровня по умолчанию
    logger.setDefaultLevel(static_cast<int>(NatureLevel::Rain));
    logger.log("Test message with new default level.");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testLogger();
    return 0;
}
