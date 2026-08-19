CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

TARGET = wrapper.exe

SRC = wrapper.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)