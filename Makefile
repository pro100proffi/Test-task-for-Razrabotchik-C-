# ���������� � �����
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC
LDFLAGS = -shared

# ����� ������
TARGET_LIB = liblogger.so
SRCS_LIB = Logger.cpp
OBJS_LIB = $(SRCS_LIB:.cpp=.o)

TARGET_APP = logger_app
SRCS_APP = main.cpp
OBJS_APP = $(SRCS_APP:.cpp=.o)

# ��������� ���� ��� ������
TARGET_TEST = logger_test
SRCS_TEST = test.cpp
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

# ���� �� ���������
all: $(TARGET_LIB) $(TARGET_APP) $(TARGET_TEST)

# ������ ������������ ����������
$(TARGET_LIB): $(OBJS_LIB)
	$(CXX) $(LDFLAGS) -o $(TARGET_LIB) $(OBJS_LIB)

# ������ ����������
$(TARGET_APP): $(OBJS_APP) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_APP) $(OBJS_APP) -L. -llogger

# ������ ������
$(TARGET_TEST): $(OBJS_TEST) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(OBJS_TEST) -L. -llogger

# ���������� �������� ������
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# �������
clean:
	rm -f $(OBJS_LIB) $(OBJS_APP) $(OBJS_TEST) $(TARGET_LIB) $(TARGET_APP) $(TARGET_TEST)

.PHONY: all clean test