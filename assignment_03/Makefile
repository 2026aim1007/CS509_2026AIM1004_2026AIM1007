# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = driver_app

# List of source files
# TODO: Buddy will append src/maxflow.cpp, src/mst.cpp, and src/csr.cpp to this list later
SRCS = driver/driver.cpp src/gradientDescent.cpp ../utility/testing_utils.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) driver_app.exe