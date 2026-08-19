# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

TARGET = driver_app

SRCS = driver/driver.cpp src/csr.cpp src/bfs.cpp src/dfs.cpp src/sssp.cpp ../utility/testing_utils.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) driver_app.exe