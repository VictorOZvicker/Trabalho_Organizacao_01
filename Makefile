CXX = g++
CPPFLAGS = -Iincludes
CXXFLAGS = -std=c++20

TARGET = main.exe
SRCS = main.cpp $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
    CLEAN_CMD = del /Q /F
    CLEAN_PATHS = main.o src\*.o
else
    CLEAN_CMD = rm -f
    CLEAN_PATHS = main.o src/*.o
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@
	$(MAKE) clean

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(CLEAN_CMD) $(CLEAN_PATHS)