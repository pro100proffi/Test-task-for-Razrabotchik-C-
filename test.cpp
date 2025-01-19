#include "Logger.h"
#include <cassert>
#include <iostream>

void testLogger() {
    Logger logger("test_log.txt", Theme::Standard);

    // �������� ����������� ��������
    logger.log("Test info message.", static_cast<int>(StandardLevel::Info));
    logger.log("Test warning message.", static_cast<int>(StandardLevel::Warning));
    logger.log("Test error message.", static_cast<int>(StandardLevel::Error));

    // �������� ������ �� ��������� (Unknown)
    logger.log("Test default level message.");

    // �������� ��������� ��������
    logger.setTheme(Theme::Nature);
    logger.log("Test breeze message.", static_cast<int>(NatureLevel::Breeze));

    // �������� ��������� ������ �� ���������
    logger.setDefaultLevel(static_cast<int>(NatureLevel::Rain));
    logger.log("Test message with new default level.");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testLogger();
    return 0;
}