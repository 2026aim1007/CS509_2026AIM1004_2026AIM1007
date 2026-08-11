CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O3

TARGET = driver_app.exe

SRCS = driver/driver.cpp \
       src/triangle.cpp \
       src/triangle_optimized.cpp \
       src/betweenness_centrality.cpp \
       src/components.cpp \
       ../utility/csr.cpp \
       ../utility/testing_utils.cpp \
       ../utility/bfs.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)