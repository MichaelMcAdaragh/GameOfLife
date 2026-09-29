CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.. /raylib/src
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = GameOfLifeMain.cpp GameOfLifeFuncs.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = game_of_life

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
