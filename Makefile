# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC
LDFLAGS = -shared

# Имена файлов
TARGET_LIB = liblogger.so
SRCS_LIB = Logger.cpp
OBJS_LIB = $(SRCS_LIB:.cpp=.o)

TARGET_APP = logger_app
SRCS_APP = main.cpp
OBJS_APP = $(SRCS_APP:.cpp=.o)

# Добавляем цель для тестов
TARGET_TEST = logger_test
SRCS_TEST = test.cpp
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

# Цели по умолчанию
all: $(TARGET_LIB) $(TARGET_APP) $(TARGET_TEST)

# Сборка динамической библиотеки
$(TARGET_LIB): $(OBJS_LIB)
	$(CXX) $(LDFLAGS) -o $(TARGET_LIB) $(OBJS_LIB)

# Сборка приложения
$(TARGET_APP): $(OBJS_APP) $(TARGET_LIB)
    $(CXX) $(CXXFLAGS) -o $(TARGET_APP) $(OBJS_APP) -L. -llogger -Wl,-rpath,.

# Сборка тестов
$(TARGET_TEST): $(OBJS_TEST) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(OBJS_TEST) -L. -llogger

# Компиляция исходных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS_LIB) $(OBJS_APP) $(OBJS_TEST) $(TARGET_LIB) $(TARGET_APP) $(TARGET_TEST)

.PHONY: all clean test
